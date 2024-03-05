#include "../../include/FileOps/FileOpsUtility.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace FileOps {

    void FileOpsUtility::createAndSaveFile() {
        std::cout
            << "Enter text to be saved in the file. End with EOF (Ctrl+D/Ctrl+Z):"
            << std::endl;
        std::string userInput;
        std::stringstream inputBuffer;
        std::string tempLine;

        // Read input until EOF.
        while (std::getline(std::cin, tempLine)) {
            inputBuffer << tempLine << '\n';
        }

        userInput = inputBuffer.str();
    }

    void FileOpsUtility::readFiles() { std::cout << "readFiles" << std::endl; }

} // namespace FileOps
