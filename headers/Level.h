#ifndef QUIZ_LOGO_LEVEL_H
#define QUIZ_LOGO_LEVEL_H
#include <iostream>
#include <fstream>

class Level {
protected:
    int Length;
    bool Solved;
    std::string Name;
public:
    Level() = default;
    ~Level() = default;

    static void printBox(int l) {
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

    virtual void printLogo(std::string nume) = 0;

    [[nodiscard]] int getLength() const {
        return Length;
    }

    void setLength(int length) {
        Length = length;
    }

    [[nodiscard]] const std::string& getName() const {
        return Name;
    }

    void setName(const std::string& name) {
        Name = name;
    }

    [[nodiscard]] bool isSolved() const {
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

class Cars : public Level{
public:
    Cars() = default;
    virtual ~Cars() = default;

    void printLogo(std::string nume) override{
        nume = "logos/cars/" + nume + ".txt";
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
};

class Entertainment : public Level{
public:
    Entertainment() = default;
    virtual ~Entertainment() = default;

    void printLogo(std::string nume) override{
        nume = "logos/entertainment/" + nume + ".txt";
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
};

class Consumer : public Level{
public:
    Consumer() = default;
    virtual ~Consumer() = default;

    void printLogo(std::string nume) override{
        nume = "logos/consumer/" + nume + ".txt";
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
};


#endif //QUIZ_LOGO_LEVEL_H
