#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <vector>
#include <stdexcept>
#include "headers/Player.h"
#include "headers/Level.h"
#include "headers/Leaderboard.h"

enum Category {
    CARS,
    CONSUMER,
    ENTERTAINMENT
};

std::vector<Level*> createObjects(Category category) {
    std::vector<Level*> items;
    for (int i = 0; i < 20; ++i) {
        switch (category) {
            case CARS:
                items.push_back(new Cars());
                break;
            case ENTERTAINMENT:
                items.push_back(new Entertainment());
                break;
            case CONSUMER:
                items.push_back(new Consumer());
                break;
            default:
                break;
        }
    }
    return items;
}

void displayObject(Level* item, int x, const std::string& nume) {
    if(x == 1) {
        Cars *Ptr = dynamic_cast<Cars *>(item);
        if (Ptr) {
            Ptr->printLogo(nume);
        }
    }
    else if (x == 2) {
        auto *Ptr = dynamic_cast<Entertainment*>(item);
        if (Ptr) {
            Ptr->printLogo(nume);
        }
    }
    else {
        auto *Ptr = dynamic_cast<Consumer*>(item);
        if(Ptr){
            Ptr->printLogo(nume);
        }
    }
}

bool correct = true;
int min = 1;
int max = 20;

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

int main() {
    quiz();
    std::string nume;
    std::cout << "Nume Jucator:" << std::endl;
    std::getline(std::cin, nume);
    Player Player(nume, 0);

    /*std::string mod;
    int x;
    std::cout<<"Alegeti categoria (1 - MASINI / 2 - ENTERTAINMENT / 3 - GOODS)" << std::endl;
    std::cin >> mod;
    try{
        x = std::stoi(mod);
        if(x != 1 && x != 2 && x != 3) {
            throw std::invalid_argument("Numar invalid! Alegeti intre 1 , 2 sau 3.");
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << "Eroare: " << e.what() << std::endl;
        return 1;
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Eroare: " << e.what() << std::endl;
        return 1;
    }
    catch (const std::exception& e) {
        std::cerr << "Eroare: " << e.what() << std::endl;
        return 1;
    }*/

    std::vector<Level*> level = createObjects(ENTERTAINMENT);
    std::string line;
    std::string s = "logos/entertainment/nivele.txt";
    std::ifstream file(s);
    if (file.is_open()) {
        int i = 0;
        while (getline(file, line)) {
            int len = line.size();
            level[i]->setName(line);
            level[i]->setLength(len);
            i++;
        }
        file.close();
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    std::string input;

    while (correct) {
        do {
            std::uniform_int_distribution<> dis(min, max);
            int v = dis(gen);
            while (level[v]->isSolved()) {
                v = dis(gen);
            }
            std::string answer = level[v]->getName();
            std::cout << "Numiti Brand-ul sau apasati tasta Q pentru a iesi: \n" << std::endl;
            displayObject(level[v], 2,level[v]->getName());
            level[v]->printBox(level[v]->getLength());
            std::getline(std::cin, input);
            std::transform(input.begin(), input.end(), input.begin(), ::tolower);
            if (input == answer) {
                int hs = Player.getHighscore();
                hs++;
                Player.setHighscore(hs);
                level[v]->setSolved(true);
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
