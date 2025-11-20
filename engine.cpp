#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Movie {
    string title;
    string genre;
    double rating;
    string image_url;
};

vector<Movie> getDatabase() {
    return {
        {"The Dark Knight", "Action", 9.0, "https://image.tmdb.org/t/p/w500/qJ2tW6WMUDux911r6m7haRef0WH.jpg"},
        {"Inception", "Sci-Fi", 8.8, "https://image.tmdb.org/t/p/w500/9gk7adHYeDvHkCSEqAvQNLV5Uge.jpg"},
        {"Interstellar", "Sci-Fi", 8.6, "https://th.bing.com/th/id/OIP.x0BYF2nRoBmeurBc_ZhQcAHaEK?w=265&h=180&c=7&r=0&o=7&dpr=1.3&pid=1.7&rm=3"},
        {"3 Idiots", "Comedy", 8.4, "https://www.bing.com/th/id/OIP.lYV8OrLMUDNxthXdhHxzawHaJs?w=160&h=211&c=8&rs=1&qlt=90&o=6&dpr=1.3&pid=3.1&rm=2"},
        {"12th Fail", "Drama", 9.2, "https://www.bing.com/th/id/OIP.ZHPoL0gFK4eT41QuaGlohwHaOG?w=160&h=211&c=8&rs=1&qlt=90&o=6&dpr=1.3&pid=3.1&rm=2"},
        {"Hera Pheri", "Comedy", 8.2, "https://www.bing.com/th/id/OIP.TUffuPVh-yKAVcKnsN7OrAHaLH?w=160&h=211&c=8&rs=1&qlt=90&o=6&dpr=1.3&pid=3.1&rm=2"},
        {"The Shawshank Redemption", "Drama",   9.3, "https://image.tmdb.org/t/p/w500/q6y0Go1tsGEsmtFryDOJo3dEmqu.jpg"},        
        {"Mad Max: Fury Road", "Action", 8.1, "https://image.tmdb.org/t/p/w500/8tZYtuWezp8JbcsvHYO0O46tFbo.jpg"},
        {"The Godfather", "Crime", 9.2, "https://image.tmdb.org/t/p/w500/3bhkrj58Vtu7enYsRolD1fZdja1.jpg"},
        {"Chhichhore", "Drama", 8.5, "https://www.bing.com/th/id/OIP.hocD_rvVoUk6xIHnbUgmIAHaKs?w=160&h=211&c=8&rs=1&qlt=90&o=6&dpr=1.3&pid=3.1&rm=2"}
    };
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Error: No genre provided.";
        return 1;
    }

    string searchGenre = argv[1];
    vector<Movie> allMovies = getDatabase();
    vector<Movie> recommendations;

    for (size_t i = 0; i < allMovies.size(); i++) {
        if (allMovies[i].genre == searchGenre) {
            recommendations.push_back(allMovies[i]);
        }
    }

    sort(recommendations.begin(), recommendations.end(), [](const Movie& a, const Movie& b) {
        return a.rating > b.rating;
    });

    if (recommendations.empty()) {
        cout << "No movies found for this genre." << endl;
    } else {
        for (size_t i = 0; i < recommendations.size(); i++) {
            cout << recommendations[i].title << "|" << recommendations[i].rating << "|" << recommendations[i].image_url << endl;
        }
    }

    return 0;
}