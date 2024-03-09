#include "../../include/FileOps/ReadFromFileOps.h"
#include "../../include/FileOps/FileOpsDefinitions.h"
#include "../../include/FileOps/FileBaseOps.h"
#include "../../include/FileOps/WriteToFileOps.h"
#include <iostream>

namespace FileOps {
	HeaderInfo* ReadFromFileOps::ReadFromFile(const string& directory, const char* filename) {
		std::cout << "Reading from file: " << directory << "/" << filename << std::endl;
		vector<size_t> arrFileDataSize(MAXFILE_COUNT, 0);
		vector<unique_ptr<char[]>> arrFileData(MAXFILE_COUNT);

		// Read data from the primary file and its backups.
		for (int i = 0; i < MAXFILE_COUNT; ++i) {
			string backupFileName = filename;
			if (i > 0) {
				backupFileName += "_" + to_string(i);
			}
			string filePath = getFullPath(directory, backupFileName.c_str());
			readFileData(filePath, arrFileData[i], arrFileDataSize[i]);
		}

		// Find the index of the first valid data set.
		size_t validIndex = FindValidIndex(arrFileData, arrFileDataSize);

		// Process valid data and write updates safely if valid data is found.
		if (validIndex != static_cast<size_t>(-1)) {
			HeaderInfo* rawHeaderInfo = ProcessValidData(arrFileData[validIndex].get(), arrFileDataSize[validIndex]);
			std::unique_ptr<HeaderInfo> headerInfo(rawHeaderInfo);
			if (headerInfo) {
				std::cout << "Valid data found!" << std::endl;
				std::cout << "After Reading:" << std::endl;
				PrintHeaderInfo(*headerInfo);
				// No need to write anything here, as this is just reading
				return headerInfo.release(); // This should not cause E0153 if headerInfo is std::unique_ptr
			}
		}

		return nullptr; // Return nullptr if no valid data was found or processed.
	}

	void ReadFromFileOps::readFileData(const string& fullPath, unique_ptr<char[]>& fileData, size_t& fileSize) {
		std::cout << "Reading data from file " << fullPath << std::endl;
		ifstream file(fullPath, ios::binary | ios::ate);
		if (!file) {
			std::cout << "Cannot open file: " << fullPath << std::endl;
			return; // Skip if the file can't be opened
		}

		fileSize = file.tellg();
		fileData = make_unique<char[]>(fileSize);
		file.seekg(0);
		file.read(fileData.get(), fileSize);
		std::cout << "Read " << fileSize << " bytes from file " << fullPath << std::endl;
	}

	HeaderInfo* ReadFromFileOps::ProcessValidData(char* validData, size_t dataSize) {
		// Allocate memory for HeaderInfo structure using new (preferred in C++)
		HeaderInfo* headerInfo = new HeaderInfo;
		if (!headerInfo) { // Check allocation success
			std::cerr << "Error: Failed to allocate memory for HeaderInfo." << std::endl;
			return nullptr;
		}

		// Check if dataSize is large enough to hold the file ID, read count, and CRC
		if (dataSize < 3) {
			std::cerr << "Error: Data size too small for header and CRC." << std::endl;
			delete headerInfo;
			return nullptr;
		}

		// Decrypt the data (assuming the function is implemented elsewhere)
		EncryptDecrypt(validData, dataSize);

		// Calculate CRC on the decrypted data, excluding the last byte assumed to be
		// the CRC itself
		unsigned char nCRC = CalculateCRC(validData, dataSize - 1);

		// Early return if validation fails
		if (static_cast<unsigned char>(validData[0]) != FILEID ||
			static_cast<unsigned char>(validData[dataSize - 1]) != nCRC) {
			std::cerr << "Error: Invalid file ID or CRC mismatch." << std::endl;
			delete headerInfo;
			return nullptr;
		}

		// Set header information based on validData content
		headerInfo->fileID = validData[0];
		headerInfo->readCount = validData[1] + 1;
		headerInfo->crc = nCRC;
		// Exclude fileID, readCount, CRC from payload size
		headerInfo->payloadSize = dataSize - 3;

		// Allocate memory for the payload using new[] (preferred in C++)
		headerInfo->payload.reset(new unsigned char[headerInfo->payloadSize]);
		// Check payload allocation success
		if (!headerInfo->payload) {
			std::cerr << "Error: Failed to allocate memory for payload." << std::endl;
			delete headerInfo;
			return nullptr;
		}

		// Copy the payload data into the headerInfo structure
		memcpy(headerInfo->payload.get(), validData + 2, headerInfo->payloadSize);

		std::cout << "HeaderInfo created successfully." << std::endl;
		return headerInfo;
	}


	size_t ReadFromFileOps::FindValidIndex(const vector<unique_ptr<char[]>>& arrFileData, const vector<size_t>& arrFileDataSize) {
		for (size_t i = 0; i < static_cast<unsigned long long>(MAXFILE_COUNT) - 1; ++i) {
			if (!arrFileData[i]) continue;

			for (size_t j = i + 1; j < MAXFILE_COUNT; ++j) {
				if (!arrFileData[j]) continue;

				DataBlock dataBlock1 = { arrFileData[i].get(), arrFileDataSize[i] };
				DataBlock dataBlock2 = { arrFileData[j].get(), arrFileDataSize[j] };

				// Debug prints
				cout << "Comparing data blocks: " << endl;
				cout << "Data Block 1: ";
				for (size_t k = 0; k < dataBlock1.size; ++k) {
					cout << dataBlock1.data[k] << " ";
				}
				cout << endl;
				cout << "Data Block 2: ";
				for (size_t k = 0; k < dataBlock2.size; ++k) {
					cout << dataBlock2.data[k] << " ";
				}
				cout << endl;

				if (PerformDataComparison(&dataBlock1, &dataBlock2)) {
					cout << "Data blocks match. Index: " << i << endl;
					return i;
				}
			}
		}
		cout << "No valid index found." << endl;
		return static_cast<size_t>(-1);  // No valid index found
	}


	bool ReadFromFileOps::PerformDataComparison(const DataBlock* dataBlock1, const DataBlock* dataBlock2) {
		if (dataBlock1->size != dataBlock2->size) {
			return false;
		}
		return memcmp(dataBlock1->data, dataBlock2->data, dataBlock1->size) == 0;
	}
}
