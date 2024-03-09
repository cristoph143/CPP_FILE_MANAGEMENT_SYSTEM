#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

namespace FileOps {

	class FileOpsUtility {
	public:
		static void createAndSaveFile();
		static void readFiles();
		static string getFilenameFromUser(const string& prompt, const string& defaultFilename);
	};

}
