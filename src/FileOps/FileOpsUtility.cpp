#include "../../include/FileOps/FileOpsUtility.h"
#include "../../include/FileOps/FileOps.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace FileOps {

    void FileOpsUtility::createAndSaveFile() {
        std::cout << "Enter text to be saved in the file. End with EOF (Ctrl+D/Ctrl+Z):" << std::endl;
        std::string userInput;
        std::stringstream inputBuffer;
        std::string tempLine;

        // Read input until EOF.
        while (std::getline(std::cin, tempLine)) {
            inputBuffer << tempLine << '\n';
        }

        userInput = inputBuffer.str();

        // Assuming HeaderInfo accepts a vector for the payload directly or has a mechanism to set payload.
        std::vector<unsigned char> payload(userInput.begin(), userInput.end());

        // Construct header info.
        HeaderInfo header;
        header.fileID = FILEID;  // Assuming FILEID is defined in "FileOps.h" or the included headers therein.
        header.readCount = 0;    // Initial read count is typically zero.
        header.payload = std::make_unique<unsigned char[]>(payload.size());
        memcpy(header.payload.get(), payload.data(), payload.size());
        header.payloadSize = payload.size();

        // Specify a file name for output.
        const std::string fileName = "output.txt";
        WriteToFile(fileName.c_str(), header);  // Make sure WriteToFile accepts the proper arguments.
    }

    void FileOpsUtility::readFiles() {
        std::cout << "Read files" << std::endl;

        // Specify the file name to read from, which should match the one used in createAndSaveFile.
        const std::string fileName = "output.txt";
        HeaderInfo* header = ReadFromFile(fileName.c_str());  // Ensure that ReadFromFile accepts the file name correctly.

        if (header) {
            std::cout << "File read successfully. Content:\n";
            std::string content(header->payload.get(), header->payload.get() + header->payloadSize);
            std::cout << content << std::endl;

            // Cleanup: free the allocated HeaderInfo structure.
            delete header;
        }
        else {
            std::cout << "Failed to read file." << std::endl;
        }
    }

} // namespace FileOps
