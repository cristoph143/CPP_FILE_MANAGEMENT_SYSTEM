#include "../../include/FileOps/FileBaseOps.h"

namespace fs = filesystem;
using namespace std;
namespace FileOps {
	/**
	 * Creates a new directory at the specified path if it doesn't already exist.
	 *
	 * @param path The filesystem path where the new directory will be created.
	 */
	void FileOpsBase::createDirectory(const string& path) {
		try {
			if (!fs::exists(path)) {
				if (fs::create_directory(path)) {
					cout << "Directory created: " << path << endl;
				}
				else {
					cerr << "Failed to create directory: " << path << endl;
				}
			}
			else {
				cout << "Directory already exists: " << path << endl;
			}
		}
		catch (const fs::filesystem_error& e) {
			cerr << "Error creating directory: " << e.what() << endl;
		}
	}

	/**
	 * Constructs the full path for a file within a specified directory. Creates the directory
	 * if it does not exist.
	 *
	 * @param directory The directory in which the file is located or will be created.
	 * @param filename The name of the file.
	 * @return A string representing the full filesystem path to the file.
	 */
	string FileOpsBase::getFullPath(const string& directory, const string& filename) {
		fs::path dirPath(directory);
		if (!fs::exists(dirPath)) {
			cout << "Creating directory: " << dirPath << endl;
			fs::create_directories(dirPath); // This creates all directories in the path if not present.
		}
		return (dirPath / filename).string();
	}

	/**
	 * Checks whether a file exists at the specified path.
	 *
	 * @param name The full path to the file.
	 * @return True if the file exists, false otherwise.
	 */
	bool FileOpsBase::FileExists(const string& name) {
		struct stat buffer;
		return (stat(name.c_str(), &buffer) == 0);
	}

	/**
	 * Calculates a simple checksum (CRC) for a block of data.
	 *
	 * @param pData Pointer to the data block.
	 * @param nDataSize The size of the data block.
	 * @return The calculated CRC value as an unsigned char.
	 */
	unsigned char FileOpsBase::CalculateCRC(const char* pData, size_t nDataSize) {
		// Early return if the data pointer is NULL to avoid dereferencing NULL
		if (pData == nullptr || nDataSize == 0) {
			return 0; // Return 0 or an appropriate error code
		}

		unsigned char crc = 0;
		for (size_t i = 0; i < nDataSize; ++i) {
			crc ^= static_cast<unsigned char>(pData[i]);
		}
		return crc;
	}

	/**
	 * Encrypts or decrypts a block of data in place using a simple bitwise NOT operation.
	 *
	 * @param pData Pointer to the data block.
	 * @param nDataSize The size of the data block.
	 */
	void FileOpsBase::EncryptDecrypt(char* pData, size_t nDataSize) {
		for (size_t i = 0; i < nDataSize; ++i) {
			pData[i] = ~pData[i];
		}
	}

	/**
	 * Generates a backup filename for a given file and backup index.
	 *
	 * @param filename The original filename.
	 * @param backupID The backup index.
	 * @return A string containing the backup filename.
	 */
	string FileOpsBase::GetBackupFilename(const char* filename, int backupID) {
		string result(filename);
		result += "_" + to_string(backupID);
		return result;
	}

	/**
	 * Prints the information contained in a HeaderInfo structure in a readable format.
	 *
	 * @param header The HeaderInfo structure containing the information to be printed.
	 */
	void FileOpsBase::PrintHeaderInfo(const HeaderInfo& header) {
		cout << "Header Information:" << endl;
		cout << "File ID: " << static_cast<int>(header.fileID) << endl;
		cout << "Read Count: " << static_cast<int>(header.readCount) << endl;
		cout << "CRC: " << static_cast<int>(header.crc) << endl;
		cout << "Payload Size: " << header.payloadSize << endl;
		// If you want to print payload content, ensure it's in a readable format
		cout << "Payload: ";
		for (size_t i = 0; i < header.payloadSize; ++i) {
			cout << header.payload[i];
		}
		cout << endl;
	}
}