#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include "headers/Player.h"
#include "headers/Level.h"
#include "headers/Leaderboard.h"

bool correct = true;
int min = 1;
int max = 20;
Cars level[21];

void quiz() {
    std::cout << " ___       ________  ________  ________          ________  ___  ___  ___  ________     " << std::endl;
    std::cout << "|\\  \\     |\\   __  \\|\\   ____\\|\\   __  \\        |\\   __  \\|\\  \\|\\  \\|\\  \\|\\_____  \\    " << std::endl;
    std::cout << "\\ \\  \\    \\ \\  \\|\\  \\ \\  \\___|\\ \\  \\|\\  \\       \\ \\  \\|\\  \\ \\  \\\\\\  \\ \\  \\\\|___/  /|   " << std::endl;
    std::cout << " \\ \\  \\    \\ \\  \\\\\\  \\ \\  \\  __\\ \\  \\\\\\  \\       \\ \\  \\\\\\  \\ \\  \\\\\\  \\ \\  \\   /  / /   " << std::endl;
    std::cout << "  \\ \\  \\____\\ \\  \\\\\\  \\ \\  \\|\\  \\ \\  \\\\\\  \\       \\ \\  \\\\\\  \\ \\  \\\\\\  \\ \\  \\ /  /_/__  " << std::endl;
    std::cout << "   \\ \\_______\\ \\_______\\ \\_______\\ \\_______\\       \\ \\_____  \\ \\_______\\ \\__\\\\________\\" << std::endl;
    std::cout << "    \\|_______|\\|_______|\\|_______|\\|_______|        \\|___| \\__\\|_______|\\|__|\\|_______|" << std::endl;
    std::cout << "                                                          \\|__|                        " << std::endl;
    std::cout << "                                                                                       " << std::endl;

}

void levelRead(){
    std::string line;
    std::ifstream file("logos/cars/nivele.txt");
    if (file.is_open()) {
        int i = 1;
        while (getline(file, line)) {
            int len = line.size();
            level[i].setLength(len);
            level[i].setName(line);
            i++;
        }
        file.close();
    }
}

int main() {
    quiz();
    std::string nume;
    std::cout << "Nume Jucator:" << std::endl;
    std::getline(std::cin, nume);
    Player Player(nume, 0);
    levelRead();

    std::random_device rd;
    std::mt19937 gen(rd());

    std::string input;

    while (correct) {
        do {
            std::uniform_int_distribution<> dis(min, max);
            int v = dis(gen);
            while (level[v].isSolved() == true) {
                v = dis(gen);
            }
            std::string answer = level[v].getName();
            std::cout << "Numiti Brand-ul sau apasati tasta Q pentru a iesi: \n" << std::endl;
            level[v].printLogo(answer);
            level[v].printBox(level[v].getLength());
            std::getline(std::cin, input);
            std::transform(input.begin(), input.end(), input.begin(), ::tolower);
            if (input == answer) {
                int hs = Player.getHighscore();
                hs++;
                Player.setHighscore(hs);
                level[v].setSolved(true);
                system("cls");
            }
            else {
                correct = false;
                break;
            }
            if (Player.getHighscore() == 20)
                break;
        } while (input != "q");
        if (input == "q")
        {
            std::cout << "Quit game" << std::endl;
            break;
        }
        if (Player.getHighscore() == 20)
            break;
    }

    Leaderboard l;
    l.addPlayer(Player.getName(), Player.getHighscore());

    if (Player.getHighscore() == 20)
        std::cout << "Ai castigat! (20/20)" << std::endl;
    else
        operator<<(std::cout, Player);

    l.displayLeaderboard();
    return 0;
}

