#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <cstdlib>

using namespace std;

struct Movie {
    string title;
    string genre;
    double rating;
    string image_url;
    int    year;
    string director;
    string synopsis;
    string cast;
};

vector<Movie> getDatabase() {
    return {
        // ══════════ ACTION ══════════
        {"The Dark Knight",         "Action", 9.0, "https://image.tmdb.org/t/p/w500/qJ2tW6WMUDux911r6m7haRef0WH.jpg", 2008, "Christopher Nolan",
         "When the menace known as the Joker wreaks havoc on Gotham, Batman must confront one of the greatest psychological tests of his ability to fight injustice.",
         "Christian Bale, Heath Ledger, Aaron Eckhart"},
        {"The Matrix",              "Action", 8.7, "https://image.tmdb.org/t/p/w500/f89U3ADr1oiB1s9GkdPOEpXUk5H.jpg", 1999, "Lana & Lilly Wachowski",
         "A computer hacker learns from mysterious rebels about the true nature of his reality and his role in the war against its controllers.",
         "Keanu Reeves, Laurence Fishburne, Carrie-Anne Moss"},
        {"Gladiator",               "Action", 8.5, "https://image.tmdb.org/t/p/w500/ty8TGRuvJLPUmAR1H1nRIsgwvim.jpg", 2000, "Ridley Scott",
         "A betrayed Roman general vows revenge against the emperor who murdered his family and enslaved him — fighting as a gladiator in the arena.",
         "Russell Crowe, Joaquin Phoenix, Connie Nielsen"},
        {"Top Gun: Maverick",       "Action", 8.3, "https://image.tmdb.org/t/p/w500/n0YuM4f5lvGAP6MAW2kBIzugXnc.jpg", 2022, "Joseph Kosinski",
         "After 30+ years of service, Pete Mitchell trains a new generation of Top Gun graduates for a near-suicidal mission against all odds.",
         "Tom Cruise, Miles Teller, Jennifer Connelly"},
        {"Mad Max: Fury Road",      "Action", 8.1, "https://image.tmdb.org/t/p/w500/8tZYtuWezp8JbcsvHYO0O46tFbo.jpg", 2015, "George Miller",
         "In a post-apocalyptic wasteland, Max teams up with the mysterious Furiosa to flee from a cult leader across the scorched desert.",
         "Tom Hardy, Charlize Theron, Nicholas Hoult"},
        {"Die Hard",                "Action", 8.2, "https://image.tmdb.org/t/p/w500/yFihWxQcmqcaBR31QM6Y8gT6aYV.jpg", 1988, "John McTiernan",
         "A New York cop single-handedly holds off a group of terrorists who have taken over a Los Angeles skyscraper during a Christmas party.",
         "Bruce Willis, Alan Rickman, Bonnie Bedelia"},
        {"John Wick",               "Action", 7.4, "https://image.tmdb.org/t/p/w500/fZPSd91yGE9fCcCe6OoQr6E3Bev.jpg", 2014, "Chad Stahelski",
         "An ex-hitman comes out of retirement to track down the gangsters who killed his dog — a last gift from his recently deceased wife.",
         "Keanu Reeves, Michael Nyqvist, Alfie Allen"},
        {"Mission: Impossible - Fallout","Action",7.7,"https://image.tmdb.org/t/p/w500/AkJQpZp9WoNdj7pLYSj1L0RcMMN.jpg",2018,"Christopher McQuarrie",
         "Ethan Hunt and his IMF team race against time after a mission gone wrong, with CIA assassin August Walker sent to ensure they succeed.",
         "Tom Cruise, Henry Cavill, Ving Rhames"},
        {"Avengers: Endgame",       "Action", 8.4, "https://image.tmdb.org/t/p/w500/or06FN3Dka5tukK1e9sl16pB3iy.jpg", 2019, "Anthony & Joe Russo",
         "After the cataclysmic events of Infinity War, the Avengers assemble once more to reverse Thanos's actions and restore balance to the universe.",
         "Robert Downey Jr., Chris Evans, Mark Ruffalo"},
        {"Black Panther",           "Action", 7.3, "https://image.tmdb.org/t/p/w500/uxzzxijgPIY7slzFvMotPv8wjKA.jpg", 2018, "Ryan Coogler",
         "T'Challa returns home to the isolated technologically advanced African nation of Wakanda to serve as his country's new king.",
         "Chadwick Boseman, Michael B. Jordan, Lupita Nyong'o"},
        {"Dunkirk",                 "Action", 7.9, "https://image.tmdb.org/t/p/w500/ebSnODDg9lbsMIaWg2uAbjn7TO5.jpg", 2017, "Christopher Nolan",
         "Allied soldiers from Belgium, the British Empire, and France are surrounded by the German Army and evacuated during World War II.",
         "Fionn Whitehead, Tom Hardy, Mark Rylance"},

        // ══════════ SCI-FI ══════════
        {"Inception",               "Sci-Fi", 8.8, "https://image.tmdb.org/t/p/w500/9gk7adHYeDvHkCSEqAvQNLV5Uge.jpg", 2010, "Christopher Nolan",
         "A thief who steals secrets through dream-sharing is given a final task: plant an idea inside a CEO's mind. But his hidden secret may doom them all.",
         "Leonardo DiCaprio, Joseph Gordon-Levitt, Elliot Page"},
        {"Interstellar",            "Sci-Fi", 8.6, "https://image.tmdb.org/t/p/w500/rAiYTfKGqDCRIIqo664sY9XZIvQ.jpg", 2014, "Christopher Nolan",
         "A team of astronauts travel through a wormhole in space in a desperate attempt to ensure humanity's survival as Earth's resources run out.",
         "Matthew McConaughey, Anne Hathaway, Jessica Chastain"},
        {"2001: A Space Odyssey",   "Sci-Fi", 8.3, "https://image.tmdb.org/t/p/w500/ve72VxNqjGM69Uky4WTo2bK6rfq.jpg", 1968, "Stanley Kubrick",
         "A mysterious black monolith influences human evolution across eons, while an astronaut crew and their AI HAL 9000 head toward Jupiter.",
         "Keir Dullea, Gary Lockwood, William Sylvester"},
        {"Blade Runner 2049",       "Sci-Fi", 8.0, "https://image.tmdb.org/t/p/w500/gajva2L0rPYkEWjzgFlBXCAVBE5.jpg", 2017, "Denis Villeneuve",
         "A young blade runner discovers a secret that threatens to plunge what remains of society into chaos, leading him to track down a long-missing predecessor.",
         "Ryan Gosling, Harrison Ford, Ana de Armas"},
        {"Dune",                    "Sci-Fi", 8.0, "https://image.tmdb.org/t/p/w500/gDzOcq0pfeCeqMBwKIJlSmQpjkZ.jpg", 2021, "Denis Villeneuve",
         "A noble family's heir is thrust into the most dangerous world imaginable to protect the most precious substance in the galaxy.",
         "Timothee Chalamet, Rebecca Ferguson, Oscar Isaac"},
        {"The Martian",             "Sci-Fi", 8.0, "https://image.tmdb.org/t/p/w500/5BHuvQ6p9kfc091Z8RiFNhCwL4b.jpg", 2015, "Ridley Scott",
         "An astronaut is left for dead on Mars and must use his ingenuity and science skills to survive while NASA devises a rescue mission.",
         "Matt Damon, Jessica Chastain, Kristen Wiig"},
        {"Ex Machina",              "Sci-Fi", 7.7, "https://image.tmdb.org/t/p/w500/dmJW8IAKHKxFNiUnoDR7JfsK7Rp.jpg", 2014, "Alex Garland",
         "A programmer is selected to administer a Turing test on an AI with a humanoid robot, leading to a profoundly unsettling experience.",
         "Domhnall Gleeson, Alicia Vikander, Oscar Isaac"},
        {"Arrival",                 "Sci-Fi", 7.9, "https://image.tmdb.org/t/p/w500/x2FJsf1ElAgr63Y3PNPtJrcmpoe.jpg", 2016, "Denis Villeneuve",
         "A linguist races to learn to communicate with alien visitors before global tensions lead to catastrophic war.",
         "Amy Adams, Jeremy Renner, Forest Whitaker"},
        {"Avatar: The Way of Water","Sci-Fi", 7.6, "https://image.tmdb.org/t/p/w500/t6HIqrRAclMCA60NsSmeqe9RmNV.jpg", 2022, "James Cameron",
         "Jake Sully and Neytiri must protect their family and the ocean world of Metkayina from a resurging human threat.",
         "Sam Worthington, Zoe Saldana, Sigourney Weaver"},
        {"Gravity",                 "Sci-Fi", 7.7, "https://image.tmdb.org/t/p/w500/kZ2nZw8D681aphje8NJi8EfbL1U.jpg", 2013, "Alfonso Cuaron",
         "Two astronauts work together to survive after an accident leaves them stranded in space with no way to contact Earth.",
         "Sandra Bullock, George Clooney"},

        // ══════════ DRAMA ══════════
        {"The Shawshank Redemption","Drama",  9.3, "https://image.tmdb.org/t/p/w500/q6y0Go1tsGEsmtFryDOJo3dEmqu.jpg", 1994, "Frank Darabont",
         "Two convicts form an unlikely friendship in prison, finding solace and eventual redemption through acts of decency in the most uncommon of places.",
         "Tim Robbins, Morgan Freeman, Bob Gunton"},
        {"Schindler's List",        "Drama",  9.0, "https://image.tmdb.org/t/p/w500/sF1U4EUQS8YHUYjNl3pMGNIQyr0.jpg", 1993, "Steven Spielberg",
         "During World War II, a German businessman saves over a thousand Polish Jewish refugees from the Holocaust by employing them in his factories.",
         "Liam Neeson, Ben Kingsley, Ralph Fiennes"},
        {"Forrest Gump",            "Drama",  8.8, "https://image.tmdb.org/t/p/w500/saHP97rTPS5eLmrLQEcANmKrsFl.jpg", 1994, "Robert Zemeckis",
         "The extraordinary life of a man with a low IQ unfolds across decades of American history — from Vietnam to Watergate to finding true love.",
         "Tom Hanks, Robin Wright, Gary Sinise"},
        {"12th Fail",               "Drama",  9.2, "https://image.tmdb.org/t/p/w500/eebUPRI4Z5e1Z7Hev4JZAwMIFkX.jpg", 2023, "Vidhu Vinod Chopra",
         "The true story of IPS Officer Manoj Kumar Sharma who rose from poverty and crushing setbacks to clear India's toughest civil service exam.",
         "Vikrant Massey, Medha Shankr, Anshuman Pushkar"},
        {"Good Will Hunting",       "Drama",  8.3, "https://image.tmdb.org/t/p/w500/z2FnLKpFi1HPO7BEJxdkv6hpJSU.jpg", 1997, "Gus Van Sant",
         "A janitor at MIT who is a math genius must work with a therapist to confront his troubled past and decide what to do with his future.",
         "Matt Damon, Robin Williams, Ben Affleck"},
        {"A Beautiful Mind",        "Drama",  8.2, "https://image.tmdb.org/t/p/w500/rEIg5yJdNOt9fmX4P8gU9LeNoTQ.jpg", 2001, "Ron Howard",
         "The story of Nobel Prize winner John Nash, a mathematical genius who battles paranoid schizophrenia with the support of his devoted wife.",
         "Russell Crowe, Ed Harris, Jennifer Connelly"},
        {"Taare Zameen Par",        "Drama",  8.5, "https://image.tmdb.org/t/p/w500/bKySGFUTgsZyn5i7s5htMVy4Xd2.jpg", 2007, "Aamir Khan",
         "A dyslexic child who struggles in school finds his world transform when an unconventional art teacher recognizes and nurtures his hidden genius.",
         "Darsheel Safary, Aamir Khan, Tisca Chopra"},
        {"Chhichhore",              "Drama",  8.5, "https://image.tmdb.org/t/p/w500/1g0dhYtq4irTY1GPXvft6k4YLjm.jpg", 2019, "Nitesh Tiwari",
         "Middle-aged friends relive their wild college years to inspire a friend's son after a devastating failure, proving life is about the journey.",
         "Sushant Singh Rajput, Shraddha Kapoor, Varun Sharma"},
        {"The Pursuit of Happyness","Drama",  8.0, "https://image.tmdb.org/t/p/w500/lBYOKAMcxIvuk9s9hMuecB9dPBV.jpg", 2006, "Gabriele Muccino",
         "A struggling salesman and single father risks everything to build a future for himself and his young son on the streets of San Francisco.",
         "Will Smith, Jaden Smith, Thandie Newton"},
        {"Dangal",                  "Drama",  8.4, "https://image.tmdb.org/t/p/w500/jLiA1WW3kL1K9lYfYmVj57RD74N.jpg", 2016, "Nitesh Tiwari",
         "A former wrestler trains his daughters to become world-class wrestlers, defying societal norms in rural India.",
         "Aamir Khan, Fatima Sana Shaikh, Sanya Malhotra"},
        {"Swades",                  "Drama",  8.2, "https://image.tmdb.org/t/p/w500/yUSL24kpHc9Nls4Pohia4shgcIM.jpg", 2004, "Ashutosh Gowariker",
         "A successful NASA scientist returns to India and is forced to face the challenges his country faces, inspiring him to make a difference.",
         "Shah Rukh Khan, Gayatri Joshi, Kishori Balal"},

        // ══════════ COMEDY ══════════
        {"3 Idiots",                "Comedy", 8.4, "https://image.tmdb.org/t/p/w500/66A9MqXOyVFCssoloscw79z8Tew.jpg", 2009, "Rajkumar Hirani",
         "Two friends search for their missing third friend while reliving how the free-spirited Rancho disrupted India's rigid education system.",
         "Aamir Khan, R. Madhavan, Sharman Joshi"},
        {"Hera Pheri",              "Comedy", 8.2, "https://image.tmdb.org/t/p/w500/s8GKTE9fLFoVSPCQr0oXGfPFL2y.jpg", 2000, "Priyadarshan",
         "Two unemployed men and their hot-tempered landlord stumble into a kidnapping ransom scheme, leading to absolute chaos and hilarity.",
         "Akshay Kumar, Suniel Shetty, Paresh Rawal"},
        {"The Grand Budapest Hotel","Comedy", 8.1, "https://image.tmdb.org/t/p/w500/eWdyYQreja6JGCzqHWXpWHDrrPo.jpg", 2014, "Wes Anderson",
         "The adventures of a legendary European hotel concierge and his young lobby boy protégé across a backdrop of wars, heists, and romance.",
         "Ralph Fiennes, Tony Revolori, Saoirse Ronan"},
        {"Andaz Apna Apna",         "Comedy", 8.0, "https://image.tmdb.org/t/p/w500/7TPYtzq9ABkfED1JB0tRASamL4z.jpg", 1994, "Rajkumar Santoshi",
         "Two dim-witted rivals compete to woo a rich heiress, leading to a series of hilarious mistaken identities and outrageous comic schemes.",
         "Aamir Khan, Salman Khan, Raveena Tandon"},
        {"Dumb and Dumber",         "Comedy", 7.3, "https://image.tmdb.org/t/p/w500/4LdpBXiCyGKkR8FGHgjKlphrfUc.jpg", 1994, "Peter Farrelly",
         "Two hopelessly dim-witted best friends embark on a cross-country road trip to return a briefcase left behind at an airport terminal.",
         "Jim Carrey, Jeff Daniels, Lauren Holly"},
        {"Superbad",                "Comedy", 7.6, "https://image.tmdb.org/t/p/w500/ek8e8txUyUwd2BNqj6lFEerJfbq.jpg", 2007, "Greg Mottola",
         "Two inseparable best friends try to score alcohol for a high school party in one wild, embarrassing, and unforgettable night.",
         "Jonah Hill, Michael Cera, Seth Rogen"},
        {"PK",                      "Comedy", 8.1, "https://image.tmdb.org/t/p/w500/okF78W1AcXAenlYFE3vna9Uuqjp.jpg", 2014, "Rajkumar Hirani",
         "An alien stranded on Earth navigates human society and religion with childlike wonder, challenging the godmen who exploit believers.",
         "Aamir Khan, Anushka Sharma, Sanjay Dutt"},
        {"Munna Bhai M.B.B.S.",     "Comedy", 8.1, "https://image.tmdb.org/t/p/w500/OjJ2eZFMr0InHxjYCQXwxDoo4v.jpg", 2003, "Rajkumar Hirani",
         "A gangster enrolls in medical school to fulfill his father's dream, charming everyone with his unconventional 'Gandhigiri' approach.",
         "Sanjay Dutt, Arshad Warsi, Gracy Singh"},

        // ══════════ CRIME ══════════
        {"The Godfather",           "Crime",  9.2, "https://image.tmdb.org/t/p/w500/3bhkrj58Vtu7enYsRolD1fZdja1.jpg", 1972, "Francis Ford Coppola",
         "An aging crime patriarch transfers control of his empire to his reluctant son in this saga of power, family, loyalty, and betrayal.",
         "Marlon Brando, Al Pacino, James Caan"},
        {"Pulp Fiction",            "Crime",  8.9, "https://image.tmdb.org/t/p/w500/d5iIlFn5s0ImszYzBPb8JPIfbXD.jpg", 1994, "Quentin Tarantino",
         "The lives of two mob hitmen, a boxer, and a gangster interweave in four non-linear tales of violence, redemption, and dark humour.",
         "John Travolta, Uma Thurman, Samuel L. Jackson"},
        {"The Departed",            "Crime",  8.5, "https://image.tmdb.org/t/p/w500/nT97ifVT2J1yMQmeq20Qblg61T.jpg", 2006, "Martin Scorsese",
         "An undercover cop and a police informant must each discover the other's identity before their covers are blown in the Boston criminal underworld.",
         "Leonardo DiCaprio, Matt Damon, Jack Nicholson"},
        {"Parasite",                "Crime",  8.5, "https://image.tmdb.org/t/p/w500/7IiTTgloJzvGI1TAYymCfbfl3vT.jpg", 2019, "Bong Joon-ho",
         "Greed and class discrimination collide when the destitute Kim family infiltrate the wealthy Park household in this Oscar-winning dark thriller.",
         "Kang-ho Song, Sun-kyun Lee, Yeo-jeong Jo"},
        {"Heat",                    "Crime",  8.3, "https://image.tmdb.org/t/p/w500/e09dLw1Ljtccd2P4NsuUvVtS5du.jpg", 1995, "Michael Mann",
         "A legendary detective and a master thief engage in an intensely personal cat-and-mouse game across the sprawling landscape of Los Angeles.",
         "Al Pacino, Robert De Niro, Val Kilmer"},
        {"Catch Me If You Can",     "Crime",  8.1, "https://image.tmdb.org/t/p/w500/a4BfxRK8dBgbQqbRxPs8kmLd8LG.jpg", 2002, "Steven Spielberg",
         "Frank Abagnale Jr. successfully passes himself off as a pilot, a doctor, and a lawyer — all before his 21st birthday — while evading an FBI agent.",
         "Leonardo DiCaprio, Tom Hanks, Christopher Walken"},
        {"No Country for Old Men",  "Crime",  8.1, "https://image.tmdb.org/t/p/w500/6d5XOczc226jECq0LIX0siKtgHR.jpg", 2007, "Coen Brothers",
         "After a hunter stumbles upon a drug deal gone wrong and takes the cash, a relentless killer and a world-weary sheriff pursue him across Texas.",
         "Tommy Lee Jones, Javier Bardem, Josh Brolin"},
        {"Gangs of Wasseypur",      "Crime",  8.2, "https://image.tmdb.org/t/p/w500/xAy208Znkingmfnb5ZbULwLyIwW.jpg", 2012, "Anurag Kashyap",
         "A saga of revenge spanning three generations of coal mafia families in Wasseypur, Jharkhand — India's most ambitious crime epic.",
         "Manoj Bajpayee, Nawazuddin Siddiqui, Richa Chadha"},

        // ══════════ THRILLER ══════════
        {"Se7en",                   "Thriller",8.6,"https://image.tmdb.org/t/p/w500/69Sns8WoET6CfaYlIkHbla4l7nC.jpg",  1995, "David Fincher",
         "Two detectives — a retiring veteran and an idealistic newcomer — hunt a serial killer who uses the seven deadly sins as motives.",
         "Brad Pitt, Morgan Freeman, Kevin Spacey"},
        {"The Silence of the Lambs","Thriller",8.6,"https://image.tmdb.org/t/p/w500/uS9m8OBk1A8eM9I042bx8XXpqAq.jpg", 1991, "Jonathan Demme",
         "A rookie FBI agent must turn to the brilliant but dangerously insane Dr. Hannibal Lecter to catch a serial killer who skins his victims.",
         "Jodie Foster, Anthony Hopkins, Scott Glenn"},
        {"Gone Girl",               "Thriller",8.1,"https://image.tmdb.org/t/p/w500/ts996lKsxvjkO2yiYG0ht4qAicO.jpg",  2014, "David Fincher",
         "On their fifth anniversary, Nick Dunne's wife Amy mysteriously disappears. Under pressure from police and the media, he unpacks the truth.",
         "Ben Affleck, Rosamund Pike, Neil Patrick Harris"},
        {"Prisoners",               "Thriller",8.1,"https://image.tmdb.org/t/p/w500/jsS3a3ep2KyBVmmiwaz3LvK49b1.jpg",  2013, "Denis Villeneuve",
         "When two young girls go missing, a desperate father takes the law into his own hands while a detective races against time to find them.",
         "Hugh Jackman, Jake Gyllenhaal, Viola Davis"},
        {"Oldboy",                  "Thriller",8.4,"https://image.tmdb.org/t/p/w500/pWDtjs568ZfOTMbURQBYuT4Qxka.jpg",  2003, "Park Chan-wook",
         "After being imprisoned in a cell for 15 years without knowing why, a man is abruptly freed and must find his captor within five days.",
         "Choi Min-sik, Yoo Ji-tae, Kang Hye-jung"},
        {"Knives Out",              "Thriller",7.9,"https://image.tmdb.org/t/p/w500/pThyQovXQrw2m0s9x82twj48Jq4.jpg",  2019, "Rian Johnson",
         "When renowned crime novelist Harlan Thrombey is found dead, detective Benoit Blanc is hired to investigate the wildly dysfunctional family.",
         "Daniel Craig, Chris Evans, Ana de Armas"},
        {"Zodiac",                  "Thriller",7.7,"https://image.tmdb.org/t/p/w500/6YmeO4pB7XTh8P8F960O1uA14JO.jpg",  2007, "David Fincher",
         "A cartoonist, a reporter, and a detective become obsessed with tracking down the Zodiac Killer, a serial murderer who terrorized San Francisco.",
         "Jake Gyllenhaal, Mark Ruffalo, Robert Downey Jr."},
        {"Memento",                 "Thriller",8.4,"https://image.tmdb.org/t/p/w500/yuNs09hvpHVU1cBTCAk9zxsL2oW.jpg",  2000, "Christopher Nolan",
         "A man with short-term memory loss uses tattoos and Polaroids to hunt for his wife's killer — told in reverse chronological order.",
         "Guy Pearce, Carrie-Anne Moss, Joe Pantoliano"},

        // ══════════ ANIMATION ══════════
        {"Spirited Away",           "Animation",8.6,"https://image.tmdb.org/t/p/w500/39wmItIWsg5sZMyRUHLkWBcuVCM.jpg",  2001, "Hayao Miyazaki",
         "During her family's move, a sullen girl wanders into a world ruled by gods and spirits — and must work to free herself and her parents.",
         "Daveigh Chase, Suzanne Pleshette, Miyu Irino"},
        {"Your Name",               "Animation",8.4,"https://image.tmdb.org/t/p/w500/q719jXXEzOoYaps6babgKnONONX.jpg",  2016, "Makoto Shinkai",
         "A teenage boy and girl wake up in each other's bodies in a mysterious time-swapping phenomenon, and begin to search for each other.",
         "Ryunosuke Kamiki, Mone Kamishiraishi, Masami Nagasawa"},
        {"Spider-Man: Into the Spider-Verse","Animation",8.4,"https://image.tmdb.org/t/p/w500/iiZZdoQBEYBv6id8su7ImL0oCbD.jpg",2018,"Bob Persichetti",
         "Miles Morales becomes the Spider-Man of his universe and crosses paths with five counterparts from other dimensions across the multiverse.",
         "Shameik Moore, Hailee Steinfeld, Nicolas Cage"},
        {"The Lion King",           "Animation",8.5,"https://image.tmdb.org/t/p/w500/sKCr78MXSLixwmZ8DyJLrpMsd15.jpg",  1994, "Roger Allers",
         "A young lion prince flees his kingdom after his father's murder and must find the courage to return as an adult and claim his rightful place.",
         "Matthew Broderick, Jeremy Irons, James Earl Jones"},
        {"Coco",                    "Animation",8.4,"https://image.tmdb.org/t/p/w500/gGEsBPAijhVUFoiNpgZXqRVWJt2.jpg",  2017, "Lee Unkrich",
         "A music-loving young boy is magically transported to the Land of the Dead where he seeks out his great-great-grandfather, a legendary musician.",
         "Anthony Gonzalez, Gael Garcia Bernal, Benjamin Bratt"},
        {"WALL-E",                  "Animation",8.4,"https://image.tmdb.org/t/p/w500/hbhFnRzzg6ZDmm8YAmxBnQpQIPh.jpg",  2008, "Andrew Stanton",
         "A solitary robot left to clean up Earth falls in love with EVE, a search robot, and follows her on a space adventure that will decide humanity's fate.",
         "Ben Burtt, Elissa Knight, Jeff Garlin"},
        {"Princess Mononoke",       "Animation",8.4,"https://image.tmdb.org/t/p/w500/cMYCDADoLKLbB83g4WnJegaZimC.jpg",  1997, "Hayao Miyazaki",
         "A prince with a cursed arm seeks a cure while caught in an epic conflict between the gods of a forest and the humans who exploit it.",
         "Yoji Matsuda, Yuriko Ishida, Yuko Tanaka"},

        // ══════════ HORROR ══════════
        {"Get Out",                 "Horror", 7.7, "https://image.tmdb.org/t/p/w500/tFXcEccSQMf3lfhfXKSU9iRBpa3.jpg", 2017, "Jordan Peele",
         "A Black man visits his white girlfriend's family estate, only to discover something deeply disturbing lurking beneath the polite surface.",
         "Daniel Kaluuya, Allison Williams, Bradley Whitford"},
        {"The Shining",             "Horror", 8.4, "https://image.tmdb.org/t/p/w500/b6ko0IKC8MdYBBPkkA1aBPLe2yz.jpg", 1980, "Stanley Kubrick",
         "A family heads to an isolated hotel for winter, where the father — a recovering alcoholic — descends into murderous madness.",
         "Jack Nicholson, Shelley Duvall, Danny Lloyd"},
        {"Hereditary",              "Horror", 7.3, "https://image.tmdb.org/t/p/w500/hjlZSXM86wJrfCv5VKfR5DI2VeU.jpg", 2018, "Ari Aster",
         "After their reclusive grandmother's death, the Graham family begins to unravel dark and horrifying secrets as supernatural forces descend.",
         "Toni Collette, Gabriel Byrne, Milly Shapiro"},
        {"A Quiet Place",           "Horror", 7.5, "https://image.tmdb.org/t/p/w500/nAU74GmpUk7t5iklEp3bufwDq4n.jpg", 2018, "John Krasinski",
         "A family struggles to survive in a post-apocalyptic world infested with monsters that hunt purely by sound, forced to live in near-total silence.",
         "Emily Blunt, John Krasinski, Millicent Simmonds"},
        {"The Conjuring",           "Horror", 7.5, "https://image.tmdb.org/t/p/w500/wVYREutTvI2tmxr6ujrHT704wGF.jpg", 2013, "James Wan",
         "Paranormal investigators Ed and Lorraine Warren work to help a family terrorized by a dark presence in their farmhouse in rural Rhode Island.",
         "Vera Farmiga, Patrick Wilson, Ron Livingston"},
        {"It",                      "Horror", 7.3, "https://image.tmdb.org/t/p/w500/9E2y5Q7WlCVNEhP5GiVTjhEhx1o.jpg", 2017, "Andy Muschietti",
         "Seven young outcasts in Derry, Maine, are drawn together by a deeply disturbing shapeshifting entity that exploits each of their worst fears.",
         "Bill Skarsgard, Jaeden Martell, Finn Wolfhard"},
        {"Us",                      "Horror", 6.8, "https://image.tmdb.org/t/p/w500/ux2dU1jQ2ACIMShzB3yP93Udpzc.jpg", 2019, "Jordan Peele",
         "A family's serene beach vacation turns to chaos when their terrifying doppelgangers appear and begin to terrorize them.",
         "Lupita Nyong'o, Winston Duke, Elisabeth Moss"},

        // ══════════ ROMANCE ══════════
        {"Titanic",                 "Romance", 7.9, "https://image.tmdb.org/t/p/w500/9xjZS2rlVxm8SFx8kPC3aIGCOYQ.jpg", 1997, "James Cameron",
         "A poor artist and a rich socialite fall in love aboard the ill-fated RMS Titanic, but can only one survive the shipwreck?",
         "Leonardo DiCaprio, Kate Winslet, Billy Zane"},
        {"La La Land",              "Romance", 8.0, "https://image.tmdb.org/t/p/w500/uDO8zWDhfWwoFdKS4fzkUJt0Rf0.jpg", 2016, "Damien Chazelle",
         "In modern-day Los Angeles, a jazz musician and an aspiring actress fall in love while chasing their dreams — and discover the price of ambition.",
         "Ryan Gosling, Emma Stone, John Legend"},
        {"Eternal Sunshine of the Spotless Mind","Romance",8.3,"https://image.tmdb.org/t/p/w500/5MwkWH9tYHv3mV9OdYTMR5qreIz.jpg",2004,"Michel Gondry",
         "When a couple breaks up, they each undergo a procedure to erase their memories of each other. But Joel falls in love all over again.",
         "Jim Carrey, Kate Winslet, Tom Wilkinson"},
        {"Before Sunrise",          "Romance", 8.1, "https://image.tmdb.org/t/p/w500/kf1Jb1c2JAOqjuzA3H4oDM263uB.jpg", 1995, "Richard Linklater",
         "A young American man and a French woman meet on a train and spend one magical night talking, walking, and slowly falling in love in Vienna.",
         "Ethan Hawke, Julie Delpy"},
        {"Dilwale Dulhania Le Jayenge","Romance",8.1,"https://image.tmdb.org/t/p/w500/2CAL2433ZeIihfX1Hb2139CX0pW.jpg",1995,"Aditya Chopra",
         "Two young Indians fall in love on a European trip, but must win over their traditional families to be together — especially the girl's strict father.",
         "Shah Rukh Khan, Kajol, Amrish Puri"},
        {"Kabhi Khushi Kabhie Gham","Romance",7.4,"https://image.tmdb.org/t/p/w500/j9lCK1aFXqMO3hzhGiqCNU8coIX.jpg",   2001,"Karan Johar",
         "A wealthy man's son is disowned for marrying a commoner he loves. Years later, his younger brother sets out to reunite the fractured family.",
         "Amitabh Bachchan, Shah Rukh Khan, Kajol"},
        {"Jab We Met",              "Romance",7.9,"https://image.tmdb.org/t/p/w500/iqiH6vnoEgjAypKsuIScN7JlE2j.jpg",  2007,"Imtiaz Ali",
         "A heartbroken businessman meets an irrepressibly cheerful girl on a train and, over a series of adventures, slowly falls in love.",
         "Shahid Kapoor, Kareena Kapoor, Dara Singh"},
    };
}

string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(),
              [](unsigned char c) { return static_cast<char>(tolower(c)); });
    return s;
}

string sanitize(string s) {
    replace(s.begin(), s.end(), '|', '-');
    replace(s.begin(), s.end(), '\n', ' ');
    replace(s.begin(), s.end(), '\r', ' ');
    return s;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Error: No genre provided." << endl;
        return 1;
    }

    string searchGenre = argv[1];
    string yearRange   = (argc >= 3) ? argv[2] : "all";

    char* ratingEnd = nullptr;
    double minRating = (argc >= 4) ? strtod(argv[3], &ratingEnd) : 0.0;
    if (argc >= 4 &&
        (ratingEnd == argv[3] || *ratingEnd != '\0' || minRating < 0.0 || minRating > 10.0)) {
        cout << "Error: Minimum rating must be a number between 0 and 10." << endl;
        return 1;
    }

    bool allGenres = (toLower(searchGenre) == "all");

    vector<Movie> allMovies = getDatabase();
    vector<Movie> recommendations;

    for (size_t i = 0; i < allMovies.size(); i++) {
        Movie& m = allMovies[i];

        if (!allGenres && toLower(m.genre) != toLower(searchGenre)) continue;

        if (yearRange != "all" && yearRange != "All") {
            string yr = toLower(yearRange);
            if      (yr == "1980s" && (m.year < 1980 || m.year > 1989)) continue;
            else if (yr == "1990s" && (m.year < 1990 || m.year > 1999)) continue;
            else if (yr == "2000s" && (m.year < 2000 || m.year > 2009)) continue;
            else if (yr == "2010s" && (m.year < 2010 || m.year > 2019)) continue;
            else if (yr == "2020s" && (m.year < 2020 || m.year > 2029)) continue;
        }

        if (m.rating < minRating) continue;

        recommendations.push_back(m);
    }

    sort(recommendations.begin(), recommendations.end(),
         [](const Movie& a, const Movie& b) { return a.rating > b.rating; });

    if (recommendations.empty()) {
        cout << "No movies found for this genre." << endl;
    } else {
        for (size_t i = 0; i < recommendations.size(); i++) {
            Movie& m = recommendations[i];
            cout << sanitize(m.title)     << "|"
                 << m.rating              << "|"
                 << sanitize(m.image_url) << "|"
                 << sanitize(m.genre)     << "|"
                 << m.year                << "|"
                 << sanitize(m.director)  << "|"
                 << sanitize(m.synopsis)  << "|"
                 << sanitize(m.cast)      << endl;
        }
    }
    return 0;
}