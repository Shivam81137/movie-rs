# Security Policy

## Supported versions

Only the latest commit on `main` is supported with security fixes.

## Reporting a vulnerability

Please **do not** report security vulnerabilities through public GitHub issues,
discussions, or pull requests.

Instead, use GitHub's private vulnerability reporting:

1. Open the repository's **Security** tab.
2. Select **Advisories** → **Report a vulnerability**.

Please include:

- a description of the issue and the affected endpoint or file,
- steps to reproduce,
- the potential impact,
- any suggested mitigation.

You can expect an acknowledgement within a few days. Please allow reasonable
time for a fix to be prepared before any public disclosure.

## Scope

CineMatch runs entirely locally, has no authentication, and stores user data
only in the browser. Security-relevant areas include:

- the Flask request handlers in `app.py`,
- the Python ↔ C++ subprocess boundary,
- the Content-Security-Policy and other response headers,
- dependency supply chain (`requirements.txt`).

## Secure deployment checklist

- Keep `FLASK_DEBUG` unset or `false` in any shared environment.
- Bind to `127.0.0.1` and place the app behind a TLS-terminating reverse proxy.
- Run under a dedicated, unprivileged user or container.
- Serve with a production WSGI server (for example Waitress or Gunicorn), not
  the Flask development server.
- Rebuild the C++ engine from source for the target platform; do not reuse
  binaries from another machine.
