#pragma once
#include "FileBaseOps.h"
#include "FileOpsDefinitions.h"

using namespace std;

namespace FileOps {
	class ReadFromFileOps : public FileOpsBase {
	public:
		HeaderInfo* ReadFromFile(const string& directory, const char* filename);

	private:
		HeaderInfo* ProcessValidData(char* validData, size_t dataSize);
		bool PerformDataComparison(const DataBlock* dataBlock1, const DataBlock* dataBlock2);
		void readFileData(const string& fullPath, unique_ptr<char[]>& fileData, size_t& fileSize);
		unique_ptr<HeaderInfo> ProcessValidData(const char* validData, size_t dataSize);
		size_t FindValidIndex(const vector<unique_ptr<char[]>>& arrFileData, const vector<size_t>& arrFileDataSize);
	};
}

