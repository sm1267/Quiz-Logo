//
// Created by Mae on 4/13/2024.
//

#ifndef QUIZ_LOGO_PLAYER_H
#define QUIZ_LOGO_PLAYER_H
#include <iostream>


class Player {
private:
    std::string Name;
    int Highscore;
public:
    Player(const std::string& name, int highscore) : Name(name), Highscore(highscore) {}

    Player(const Player& other) : Name{ other.Name }, Highscore{ other.Highscore } {}

    const std::string& getName() const {
        return Name;
    }

    void setName(const std::string& name) {
        Name = name;
    }

    int getHighscore() const {
        return Highscore;
    }

    void setHighscore(int highscore) {
        Highscore = highscore;
    }

    virtual ~Player() {
    }

    friend std::ostream& operator<<(std::ostream& os, const Player& player) {
        os << "Nume: " << player.Name << std::endl << "Scor: " << player.Highscore << std::endl;
        return os;
    }
};

#endif //QUIZ_LOGO_PLAYER_H
