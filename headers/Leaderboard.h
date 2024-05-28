#ifndef QUIZ_LOGO_LEADERBOARD_H
#define QUIZ_LOGO_LEADERBOARD_H
#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
class leaderboardPlayer {
public:
    std::string Name;
    T Score;

    leaderboardPlayer(const std::string& name, T score) : Name(name), Score(score){}
};

template <typename T>
bool compare(const leaderboardPlayer<T>& x, const leaderboardPlayer<T>& y) {
    return x.Score > y.Score;
}

template <typename T>
class Leaderboard {
private:
    std::vector<leaderboardPlayer<T>> Players;
    Leaderboard() = default;
    Leaderboard(const Leaderboard&) = delete;
    Leaderboard& operator=(const Leaderboard&) = delete;
public:
    static Leaderboard<T>& getInstance() {
        static Leaderboard<T> instance;
        return instance;
    }

    void addPlayer(const std::string& name, T score){
        Players.emplace_back(name,score);
    }

    void sortPlayers() {
        std::sort(Players.begin(), Players.end(), compare<T>);
    }

    void displayLeaderboard() const {
        for (const auto& player : Players){
            std::cout << player.Name << ": " << player.Score << std::endl;
        }
    }
};

#endif //QUIZ_LOGO_LEADERBOARD_H
