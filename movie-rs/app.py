from flask import Flask, render_template, request, jsonify
import subprocess
import os

app = Flask(__name__)

ALL_MOVIE_TITLES = [
    # Action
    "The Dark Knight","The Matrix","Gladiator","Top Gun: Maverick","Mad Max: Fury Road",
    "Die Hard","John Wick","Mission: Impossible - Fallout","Avengers: Endgame",
    "Black Panther","Dunkirk",
    # Sci-Fi
    "Inception","Interstellar","2001: A Space Odyssey","Blade Runner 2049","Dune",
    "The Martian","Ex Machina","Arrival","Avatar: The Way of Water","Gravity",
    # Drama
    "The Shawshank Redemption","Schindler's List","Forrest Gump","12th Fail",
    "Good Will Hunting","A Beautiful Mind","Taare Zameen Par","Chhichhore",
    "The Pursuit of Happyness","Dangal","Swades",
    # Comedy
    "3 Idiots","Hera Pheri","The Grand Budapest Hotel","Andaz Apna Apna",
    "Dumb and Dumber","Superbad","PK","Munna Bhai M.B.B.S.",
    # Crime
    "The Godfather","Pulp Fiction","The Departed","Parasite","Heat",
    "Catch Me If You Can","No Country for Old Men","Gangs of Wasseypur",
    # Thriller
    "Se7en","The Silence of the Lambs","Gone Girl","Prisoners","Oldboy",
    "Knives Out","Zodiac","Memento",
    # Animation
    "Spirited Away","Your Name","Spider-Man: Into the Spider-Verse",
    "The Lion King","Coco","WALL-E","Princess Mononoke",
    # Horror
    "Get Out","The Shining","Hereditary","A Quiet Place","The Conjuring","It","Us",
    # Romance
    "Titanic","La La Land","Eternal Sunshine of the Spotless Mind",
    "Before Sunrise","Dilwale Dulhania Le Jayenge","Kabhi Khushi Kabhie Gham",
    "Jab We Met",
]

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/autocomplete')
def autocomplete():
    query = request.args.get('q', '').lower().strip()
    if not query:
        return jsonify([])
    matches = [t for t in ALL_MOVIE_TITLES if query in t.lower()][:10]
    return jsonify(matches)

@app.route('/recommend', methods=['POST'])
def recommend():
    genre      = request.form.get('genre', '').strip()
    year_range = request.form.get('year_range', 'all').strip() or 'all'
    min_rating = request.form.get('min_rating', '0').strip() or '0'

    if not genre:
        return jsonify({"error": "No genre provided."}), 400

    engine_path = 'engine.exe' if os.name == 'nt' else './engine'
    if not os.path.exists(engine_path):
        return jsonify({"error": "Engine not compiled. Run: g++ engine.cpp -o engine.exe"}), 500

    try:
        result = subprocess.run(
            [engine_path, genre, year_range, min_rating],
            capture_output=True, text=True
        )
        movies = []
        for line in result.stdout.strip().split('\n'):
            if '|' in line:
                parts = line.split('|')
                if len(parts) >= 7:
                    movies.append({
                        'title':    parts[0].strip(),
                        'rating':   parts[1].strip(),
                        'image':    parts[2].strip(),
                        'genre':    parts[3].strip(),
                        'year':     parts[4].strip(),
                        'director': parts[5].strip(),
                        'synopsis': parts[6].strip(),
                        'cast':     parts[7].strip() if len(parts) > 7 else '',
                    })
        return jsonify(movies)
    except Exception as e:
        return jsonify({'error': str(e)}), 500

if __name__ == '__main__':
    app.run(debug=True)