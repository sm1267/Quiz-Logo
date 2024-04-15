#ifndef QUIZ_LOGO_PLAYER_H
#define QUIZ_LOGO_PLAYER_H
#include <iostream>


class Player {
private:
    std::string Name;
    int Highscore;
public:
    Player() = default;
    Player(const std::string& name, int highscore) : Name(name), Highscore(highscore) {}
    virtual ~Player() = default;

    [[nodiscard]] const std::string& getName() const {
        return Name;
    }


    [[nodiscard]] int getHighscore() const {
        return Highscore;
    }

    void setHighscore(int highscore) {
        Highscore = highscore;
    }

    friend std::ostream& operator<<(std::ostream& os, const Player& player) {
        os << "Nume: " << player.Name << std::endl << "Scor: " << player.Highscore << std::endl;
        return os;
    }

};

#endif //QUIZ_LOGO_PLAYER_H
