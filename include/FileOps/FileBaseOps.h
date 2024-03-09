#pragma once

#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>  
#include <memory>
using namespace std;
namespace fs = filesystem;

namespace FileOps {
	class FileOpsBase {
	protected:
		std::string getFullPath(const std::string& directory, const std::string& filename);
		bool FileExists(const std::string& name);
		unsigned char CalculateCRC(const char* pData, size_t nDataSize);
		void EncryptDecrypt(char* pData, size_t nDataSize);
		string GetBackupFilename(const char* filename, int backupID);

	public:
		void createDirectory(const std::string& path);
		FileOpsBase() = default;
		virtual ~FileOpsBase() = default;
	};
}
