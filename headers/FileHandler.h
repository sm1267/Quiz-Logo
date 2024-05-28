#ifndef QUIZ_LOGO_FILEHANDLER_H
#define QUIZ_LOGO_FILEHANDLER_H
#include <iostream>
#include <fstream>
#include <stdexcept>

class FileHandler {
private:
    std::ifstream file;
public:
    FileHandler(const std::string& filename): file(filename) {
        if(!file.is_open()){
            throw std::runtime_error("Fisierul nu s-a putut deschide.");
        }
    }

    ~FileHandler() {
        if (file.is_open()) {
            file.close();
        }
    }

    bool readLine(std::string& line){
        if (std::getline(file, line)) {
            return true;
        }
        return false;
    }
};

#endif //QUIZ_LOGO_FILEHANDLER_H
