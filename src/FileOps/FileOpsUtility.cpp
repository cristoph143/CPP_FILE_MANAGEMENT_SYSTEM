#include "../../include/FileOps/FileOpsUtility.h"
#include "../../include/FileOps/FileOps.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

namespace FileOps {

    void FileOpsUtility::createAndSaveFile() {
        string directoryPath = "files";
        createDirectory(directoryPath);
        cout << "Enter text to be saved in the file. End with EOF (Ctrl+D/Ctrl+Z):" << endl;
        string userInput;
        stringstream inputBuffer;
        string tempLine;

        // Read input until EOF.
        while (getline(cin, tempLine)) {
            inputBuffer << tempLine << '\n';
        }

        userInput = inputBuffer.str();

        // Assuming HeaderInfo accepts a vector for the payload directly or has a mechanism to set payload.
        vector<unsigned char> payload(userInput.begin(), userInput.end());

        // Construct header info.
        HeaderInfo header;
        header.fileID = FILEID;  // Assuming FILEID is defined in "FileOps.h" or the included headers therein.
        header.readCount = 0;    // Initial read count is typically zero.
        header.payload = make_unique<unsigned char[]>(payload.size());
        memcpy(header.payload.get(), payload.data(), payload.size());
        header.payloadSize = payload.size();

        // Specify a file name for output.
        //const string fileName = "output.txt";

        // Use getFilenameFromUser to get the filename for saving the file
        string fileName = getFilenameFromUser("Enter the filename where text will be saved:", "default_output.txt");

        WriteToFile(fileName.c_str(), header);  // Make sure WriteToFile accepts the proper arguments.
    }

    string FileOpsUtility::getFilenameFromUser(const string& prompt, const string& defaultFilename) {
        cout << prompt << endl;

        // Clear any errors with cin and ignore any leftover characters in the input buffer.
        cin.clear(); // Reset any error flags that might be set.
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear out the input buffer.

        string fileName;
        getline(cin, fileName);

        // Check if anything was entered; if not, use the default filename.
        if (fileName.empty()) {
            fileName = defaultFilename;
            cout << "No filename entered. Using default: " << fileName << endl;
        }

        return fileName;
    }


    void FileOpsUtility::readFiles() {
        cout << "Read files" << endl;

        // Get filename from user
        string fileName = getFilenameFromUser("Enter the filename to read:", "default_output.txt");


        // Specify the file name to read from, which should match the one used in createAndSaveFile.
        //const string fileName = "output.txt";
        HeaderInfo* header = ReadFromFile(fileName.c_str());  // Ensure that ReadFromFile accepts the file name correctly.

        if (header) {
            cout << "File read successfully. Content:\n";
            string content(header->payload.get(), header->payload.get() + header->payloadSize);
            cout << content << endl;

            // Cleanup: free the allocated HeaderInfo structure.
            delete header;
        }
        else {
            cout << "Failed to read file." << endl;
        }
    }

} // namespace FileOps
