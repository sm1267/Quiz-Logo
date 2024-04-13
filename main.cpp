#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>



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

class Level {
private:
    int Length;
    bool Solved;
    std::string Name;
public:
    Level() = default;
    ~Level() = default;

    void printBox(int l) {
        std::string separator = "-";
        std::string padding = "|";
        std::string text = "|";
        for (int j = 1; j <= l; ++j) {
            separator += "------";
            padding += "     |";
            char value = '?';
            text += "  ";
            text += value;
            text += "  |";
        }
        std::cout << separator << std::endl;
        std::cout << padding << std::endl;
        std::cout << text << std::endl;
        std::cout << padding << std::endl;
        std::cout << separator << std::endl;
    }

    void printLogo(std::string nume) {
        nume = "logos/" + nume + ".txt";
        std::fstream myFile;
        myFile.open(nume, std::ios::in);
        if (myFile.is_open()) {
            std::string line;
            while (getline(myFile, line)) {
                std::cout << line << std::endl;
            }
        }
        myFile.close();
        std::cout << std::endl;
    }

    int getLength() const {
        return Length;
    }

    void setLength(int length) {
        Length = length;
    }

    const std::string& getName() const {
        return Name;
    }

    void setName(const std::string& name) {
        Name = name;
    }

    bool isSolved() const {
        return Solved;
    }

    void setSolved(bool solved) {
        Solved = solved;
    }

    friend std::ostream& operator<<(std::ostream& os, const Level& level) {
        os << "Lungime: " << level.Length << " Rezolvat: " << level.Solved << " Nume: " << level.Name;
        return os;
    }
};

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

Level level[21];

int main() {
    quiz();

    std::string nume;
    std::cout << "Nume Jucator:" << std::endl;
    std::getline(std::cin, nume);
    Player Player(nume, 0);

    std::string input;


    std::string line;
    std::ifstream file("logos/nivele.txt");
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

    bool correct = true;

    std::random_device rd;
    std::mt19937 gen(rd());
    int min = 1;
    int max = 20;

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

