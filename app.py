from flask import Flask, render_template, request, jsonify
import subprocess
import os

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/recommend', methods=['POST'])
def recommend():
    genre = request.form.get('genre')
    
    # Check if C++ engine exists
    if not os.path.exists('engine.exe') and not os.path.exists('./engine'):
        return jsonify({"error": "C++ engine not compiled. Run: g++ engine.cpp -o engine"}), 500

    # Prepare command
    command = ['./engine', genre] if os.name != 'nt' else ['engine.exe', genre]
    
    try:
        # Run C++ engine
        result = subprocess.run(command, capture_output=True, text=True)
        output = result.stdout.strip().split('\n')
        
        movies = []
        for line in output:
            if "|" in line:
                parts = line.split("|")
                if len(parts) >= 3:
                    movies.append({
                        "title": parts[0], 
                        "rating": parts[1], 
                        "image": parts[2]
                    })
        
        return jsonify(movies)
        
    except Exception as e:
        return jsonify({"error": str(e)})

if __name__ == '__main__':
    app.run(debug=True)