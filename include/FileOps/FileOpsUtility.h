// include/FileOps/FileOpsUtility.h
#ifndef FILEOPSUTILITY_H
#define FILEOPSUTILITY_H

#include <string>

using namespace std;

namespace FileOps {

	class FileOpsUtility {
	public:
		static void createAndSaveFile();
		static void readFiles();
		static string getFilenameFromUser(const string& prompt, const string& defaultFilename);
	};

} // namespace FileOps

#endif // FILEOPSUTILITY_H
