"""CineMatch - Flask front end for the C++ movie recommendation engine."""

from __future__ import annotations

import os
import re
import subprocess
from pathlib import Path

from flask import Flask, jsonify, render_template, request

BASE_DIR = Path(__file__).resolve().parent

# Filters accepted by the C++ engine. Keeping these as allow-lists means user
# input is never passed through to the subprocess unchecked.
GENRES = (
    "Action",
    "Sci-Fi",
    "Drama",
    "Comedy",
    "Crime",
    "Thriller",
    "Animation",
    "Horror",
    "Romance",
)
GENRE_LOOKUP = {genre.lower(): genre for genre in GENRES}
GENRE_LOOKUP["all"] = "All"

YEAR_RANGES = {"all", "1980s", "1990s", "2000s", "2010s", "2020s"}
RATING_PATTERN = re.compile(r"^\d{1,2}(?:\.\d{1,2})?$")
MAX_QUERY_LENGTH = 64
ENGINE_TIMEOUT_SECONDS = 5

ALL_MOVIE_TITLES = [
    # Action
    "The Dark Knight", "The Matrix", "Gladiator", "Top Gun: Maverick", "Mad Max: Fury Road",
    "Die Hard", "John Wick", "Mission: Impossible - Fallout", "Avengers: Endgame",
    "Black Panther", "Dunkirk",
    # Sci-Fi
    "Inception", "Interstellar", "2001: A Space Odyssey", "Blade Runner 2049", "Dune",
    "The Martian", "Ex Machina", "Arrival", "Avatar: The Way of Water", "Gravity",
    # Drama
    "The Shawshank Redemption", "Schindler's List", "Forrest Gump", "12th Fail",
    "Good Will Hunting", "A Beautiful Mind", "Taare Zameen Par", "Chhichhore",
    "The Pursuit of Happyness", "Dangal", "Swades",
    # Comedy
    "3 Idiots", "Hera Pheri", "The Grand Budapest Hotel", "Andaz Apna Apna",
    "Dumb and Dumber", "Superbad", "PK", "Munna Bhai M.B.B.S.",
    # Crime
    "The Godfather", "Pulp Fiction", "The Departed", "Parasite", "Heat",
    "Catch Me If You Can", "No Country for Old Men", "Gangs of Wasseypur",
    # Thriller
    "Se7en", "The Silence of the Lambs", "Gone Girl", "Prisoners", "Oldboy",
    "Knives Out", "Zodiac", "Memento",
    # Animation
    "Spirited Away", "Your Name", "Spider-Man: Into the Spider-Verse",
    "The Lion King", "Coco", "WALL-E", "Princess Mononoke",
    # Horror
    "Get Out", "The Shining", "Hereditary", "A Quiet Place", "The Conjuring", "It", "Us",
    # Romance
    "Titanic", "La La Land", "Eternal Sunshine of the Spotless Mind",
    "Before Sunrise", "Dilwale Dulhania Le Jayenge", "Kabhi Khushi Kabhie Gham",
    "Jab We Met",
]

app = Flask(__name__)
app.config["MAX_CONTENT_LENGTH"] = 8 * 1024  # Filters only; no uploads are accepted.
app.json.sort_keys = False


def _engine_candidates() -> list[Path]:
    """Return engine paths in priority order."""
    override = os.environ.get("CINEMATCH_ENGINE", "").strip()
    names = ("engine.exe", "engine") if os.name == "nt" else ("engine", "engine.exe")

    candidates: list[Path] = []
    if override:
        candidates.append(Path(override).expanduser())
    for name in names:
        candidates.append(BASE_DIR / name)
        candidates.append(BASE_DIR / "output" / name)
        candidates.append(BASE_DIR / "bin" / name)
    return candidates


def find_engine() -> Path | None:
    """Locate the compiled C++ engine, or return ``None``."""
    for candidate in _engine_candidates():
        try:
            if candidate.is_file():
                return candidate.resolve()
        except OSError:
            continue
    return None


def parse_min_rating(raw_value: str) -> float | None:
    """Validate and convert a rating filter, returning ``None`` when invalid."""
    value = (raw_value or "0").strip()
    if not RATING_PATTERN.fullmatch(value):
        return None
    rating = float(value)
    return rating if 0 <= rating <= 10 else None


def parse_movies(stdout: str) -> list[dict[str, str]]:
    """Parse the engine's pipe-delimited output into JSON-ready records."""
    movies: list[dict[str, str]] = []
    for line in stdout.splitlines():
        if "|" not in line:
            continue
        parts = [part.strip() for part in line.split("|")]
        if len(parts) < 7:
            continue
        movies.append(
            {
                "title": parts[0],
                "rating": parts[1],
                "image": parts[2],
                "genre": parts[3],
                "year": parts[4],
                "director": parts[5],
                "synopsis": parts[6],
                "cast": parts[7] if len(parts) > 7 else "",
            }
        )
    return movies


@app.after_request
def add_security_headers(response):
    """Apply conservative browser security headers to every response."""
    response.headers.setdefault("X-Content-Type-Options", "nosniff")
    response.headers.setdefault("X-Frame-Options", "DENY")
    response.headers.setdefault("Referrer-Policy", "strict-origin-when-cross-origin")
    response.headers.setdefault(
        "Permissions-Policy", "camera=(), geolocation=(), microphone=()"
    )
    response.headers.setdefault(
        "Content-Security-Policy",
        "default-src 'self'; "
        "base-uri 'self'; "
        "connect-src 'self'; "
        "font-src 'self' https://fonts.gstatic.com; "
        "form-action 'self'; "
        "frame-ancestors 'none'; "
        "img-src 'self' data: https://image.tmdb.org; "
        "script-src 'self' 'unsafe-inline'; "
        "style-src 'self' 'unsafe-inline' https://fonts.googleapis.com",
    )
    if not app.debug:
        response.headers.setdefault(
            "Strict-Transport-Security", "max-age=31536000; includeSubDomains"
        )
    return response


@app.errorhandler(413)
def request_too_large(_error):
    return jsonify({"error": "Request body is too large."}), 413


@app.get("/")
def index():
    return render_template("index.html")


@app.get("/healthz")
def healthz():
    return jsonify({"status": "ok", "engine": find_engine() is not None})


@app.get("/autocomplete")
def autocomplete():
    query = (request.args.get("q") or "").strip().lower()
    if not query or len(query) > MAX_QUERY_LENGTH:
        return jsonify([])
    matches = [title for title in ALL_MOVIE_TITLES if query in title.lower()][:10]
    return jsonify(matches)


@app.post("/recommend")
def recommend():
    genre = GENRE_LOOKUP.get((request.form.get("genre") or "").strip().lower())
    if genre is None:
        return jsonify({"error": "Please choose a valid genre."}), 400

    year_range = (request.form.get("year_range") or "all").strip().lower()
    if year_range not in YEAR_RANGES:
        return jsonify({"error": "Please choose a valid year range."}), 400

    min_rating = parse_min_rating(request.form.get("min_rating", "0"))
    if min_rating is None:
        return jsonify({"error": "Minimum rating must be a number between 0 and 10."}), 400

    engine = find_engine()
    if engine is None:
        return (
            jsonify(
                {
                    "error": (
                        "Recommendation engine is not available. "
                        "Build it with `make build` and try again."
                    )
                }
            ),
            503,
        )

    try:
        result = subprocess.run(
            [str(engine), genre, year_range, f"{min_rating:g}"],
            capture_output=True,
            text=True,
            encoding="utf-8",
            errors="replace",
            timeout=ENGINE_TIMEOUT_SECONDS,
            check=False,
            cwd=str(BASE_DIR),
        )
    except subprocess.TimeoutExpired:
        app.logger.warning("Recommendation engine timed out")
        return jsonify({"error": "The recommendation engine took too long to respond."}), 504
    except OSError:
        app.logger.exception("Unable to start the recommendation engine")
        return jsonify({"error": "The recommendation engine could not be started."}), 500

    if result.returncode != 0:
        app.logger.warning(
            "Recommendation engine exited with code %s: %s",
            result.returncode,
            (result.stderr or "").strip()[:500],
        )
        return jsonify({"error": "The recommendation engine failed to process this request."}), 500

    return jsonify(parse_movies(result.stdout))


def _env_flag(name: str, default: bool = False) -> bool:
    value = os.environ.get(name)
    if value is None:
        return default
    return value.strip().lower() in {"1", "true", "yes", "on"}


def _env_port(name: str, default: int) -> int:
    try:
        port = int(os.environ.get(name, default))
    except (TypeError, ValueError):
        return default
    return port if 1 <= port <= 65535 else default


if __name__ == "__main__":
    app.run(
        host=os.environ.get("CINEMATCH_HOST", "127.0.0.1"),
        port=_env_port("CINEMATCH_PORT", 5000),
        debug=_env_flag("FLASK_DEBUG"),
    )
