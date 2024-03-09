#include "../../include/FileOps/FileBaseOps.h"

namespace fs = filesystem;
using namespace std;
namespace FileOps {
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

	string FileOpsBase::getFullPath(const string& directory, const string& filename) {
		fs::path dirPath(directory);
		if (!fs::exists(dirPath)) {
			cout << "Creating directory: " << dirPath << endl;
			fs::create_directories(dirPath); // This creates all directories in the path if not present.
		}
		return (dirPath / filename).string();
	}

	bool FileOpsBase::FileExists(const string& name) {
		struct stat buffer;
		return (stat(name.c_str(), &buffer) == 0);
	}

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


	void FileOpsBase::EncryptDecrypt(char* pData, size_t nDataSize) {
		for (size_t i = 0; i < nDataSize; ++i) {
			pData[i] = ~pData[i];
		}
	}

	string FileOpsBase::GetBackupFilename(const char* filename, int backupID) {
		string result(filename);
		result += "_" + to_string(backupID);
		return result;
	}

	// Inside your HeaderInfo definition or as a standalone function
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