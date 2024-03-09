#pragma once

#include "FileBaseOps.h"
#include "FileOpsDefinitions.h"

namespace fs = filesystem;
using namespace std;

namespace FileOps {
    class WriteToFileOps : public FileOpsBase {
    public:
        void WriteToFile(const char* fileName, const HeaderInfo& header);
        bool WriteDataFile(const char* fileName, const char* pData, size_t nDataSize);

    private:
        std::unique_ptr<char[]> PrepareDataForWrite(const HeaderInfo& header, int& totalFileSize);
    };
}
