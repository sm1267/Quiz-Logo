#ifndef QUIZ_LOGO_LEADERBOARD_H
#define QUIZ_LOGO_LEADERBOARD_H
#include <iostream>
#include <vector>
#include <algorithm>

class Leaderboard {
private:
    std::vector<Player> players;

public:
    void addPlayer(const std::string& name, int score) {
        players.push_back({ name, score });
        sortPlayers();
    }

    void sortPlayers() {
        std::sort(players.begin(), players.end(), [](const Player& a, const Player& b) {
            return a.getHighscore() > b.getHighscore();
        });
    }

    void displayLeaderboard() {
        std::cout << "Leaderboard:\n";
        for (size_t i = 0; i < players.size(); ++i) {
            std::cout << i + 1 << ". " << players[i].getName() << " - " << players[i].getHighscore() << "\n";
        }
    }

};

#endif //QUIZ_LOGO_LEADERBOARD_H
