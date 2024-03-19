#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>



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



class Jucator {
private:
    std::string Nume;
    int Highscore;
public:
    Jucator(const std::string& nume, int highscore) : Nume(nume), Highscore(highscore) {}

    Jucator(const Jucator& other) : Nume{ other.Nume }, Highscore{ other.Highscore } {}

    const std::string& getNume() const {
        return Nume;
    }

    void setNume(const std::string& nume) {
        Nume = nume;
    }

    int getHighscore() const {
        return Highscore;
    }

    void setHighscore(int highscore) {
        Highscore = highscore;
    }

    virtual ~Jucator() {
    }

    friend std::ostream& operator<<(std::ostream& os, const Jucator& jucator) {
        os << "Nume: " << jucator.Nume << std::endl << "Scor: " << jucator.Highscore << std::endl;
        return os;
    }
};

class Nivel {
private:
    int Lungime;
    bool Rezolvat;
    std::string Nume;
public:
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
        nume = nume + ".txt";
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

    int getLungime() const {
        return Lungime;
    }

    void setLungime(int lungime) {
        Lungime = lungime;
    }

    const std::string& getNume() const {
        return Nume;
    }

    void setNume(const std::string& nume) {
        Nume = nume;
    }

    bool isRezolvat() const {
        return Rezolvat;
    }

    void setRezolvat(bool rezolvat) {
        Rezolvat = rezolvat;
    }

    friend std::ostream& operator<<(std::ostream& os, const Nivel& nivel) {
        os << "Lungime: " << nivel.Lungime << " Rezolvat: " << nivel.Rezolvat << " Nume: " << nivel.Nume;
        return os;
    }
};

class Leaderboard {
private:
    std::vector<Jucator> players;

public:
    void addPlayer(const std::string& name, int score) {
        players.push_back({ name, score });
        sortPlayers();
    }

    void sortPlayers() {
        std::sort(players.begin(), players.end(), [](const Jucator& a, const Jucator& b) {
            return a.getHighscore() > b.getHighscore();  // Sort in descending order
            });
    }

    void displayLeaderboard() {
        std::cout << "Leaderboard:\n";
        for (size_t i = 0; i < players.size(); ++i) {
            std::cout << i + 1 << ". " << players[i].getNume() << " - " << players[i].getHighscore() << "\n";
        }
    }

};

Nivel Level[21];

int main() {
    quiz();

    std::string nume;
    std::cout << "Nume Jucator:" << std::endl;
    std::getline(std::cin, nume);
    Jucator Player(nume, 0);

    std::string input;

    std::string line;
    std::ifstream file("nivele.txt");
    int i = 1;
    if (file.is_open()) {
        while (getline(file, line)) {
            int len = line.size();
            Level[i].setLungime(len);
            Level[i].setNume(line);
            i++;
        }
        file.close();
    }
    
    bool correct = true;

    srand(time(0));
    int v;
    while(correct){
        do {
            v = rand() % 20 + 1;
            while(Level[v].isRezolvat() == true) {
                v = rand() % 20 + 1;
            }
            std::string answer = Level[v].getNume();
            std::cout << "Numiti Brand-ul sau apasati tasta Q pentru a iesi: \n" << std::endl;
            Level[v].printLogo(answer);
            Level[v].printBox(Level[v].getLungime());
            std::getline(std::cin, input);
            std::transform(input.begin(), input.end(), input.begin(), ::tolower);
            if (input == answer) {
                int hs = Player.getHighscore();
                hs++;
                Player.setHighscore(hs);
                Level[v].setRezolvat(true);
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
    l.addPlayer(Player.getNume(), Player.getHighscore());

    if (Player.getHighscore() == 20)
        std::cout << "Ai castigat! (20/20)" << std::endl;
    else
        operator<<(std::cout, Player);

    l.displayLeaderboard();
    return 0;
}
