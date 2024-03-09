#include "../../include/FileOps/WriteToFileOps.h"
#include "../../include/FileOps/FileOpsDefinitions.h"
#include "../../include/FileOps/FileBaseOps.h"

namespace FileOps {
	/**
	 * Writes data to a file based on provided header information.
	 *
	 * This function writes the payload contained within the header information to a specified file.
	 * It prepares the data for writing, constructs the full file path, and writes the data to the file system.
	 *
	 * @param fileName The name of the file where data will be written.
	 * @param header The header information containing the payload and related metadata.
	 */
	void WriteToFileOps::WriteToFile(const char* fileName, const HeaderInfo& header) {
		cout << "Current working directory: " << filesystem::current_path() << endl;

		if (!fileName) {
			cerr << "Error: Null file name provided.\n";
			return;
		}

		if (!header.payload) {
			cerr << "Error: Null payload in header.\n";
			return;
		}

		cout << "Attempting to write to file: " << fileName << endl;

		int totalFileSize;
		auto pDataToWrite = PrepareDataForWrite(header, totalFileSize);

		if (!pDataToWrite) {
			cerr << "Error: Failed to prepare data for writing.\n";
			return;
		}

		// Construct the full path based on the current working directory
		string filePath = getFullPath("files", fileName);
		cout << "Writing to: " << filePath << endl;

		if (!WriteDataFile(filePath.c_str(), pDataToWrite.get(), totalFileSize)) {
			cerr << "Error: Failed to write main data file: " << filePath << endl;
		}
		else {
			cout << "Main file written successfully: " << filePath << endl;
		}
	}
	/**
	 * Prepares data for writing based on the given header information.
	 *
	 * This function prepares a buffer with the payload data from the header, appends necessary metadata
	 * like file ID and read count, computes a CRC for integrity checking, and applies simple encryption.
	 *
	 * @param header The header information containing the payload and related metadata.
	 * @param totalFileSize Outputs the total size of the prepared data.
	 * @return A unique_ptr to a char array containing the prepared data for writing.
	 */
	unique_ptr<char[]> WriteToFileOps::PrepareDataForWrite(const HeaderInfo& header, int& totalFileSize) {
		totalFileSize = static_cast<int>(header.payloadSize) + HEADER_SIZE + CRC_SIZE;
		unique_ptr<char[]> pDataToWrite(new char[totalFileSize]);

		pDataToWrite[0] = header.fileID;
		pDataToWrite[1] = header.readCount;

		// Copy payload if it exists
		if (header.payload) {
			memcpy(pDataToWrite.get() + HEADER_SIZE, header.payload.get(), header.payloadSize);
		}

		// Example CRC and encryption (simplified and for illustration)
		unsigned char crc = CalculateCRC(pDataToWrite.get(), totalFileSize - CRC_SIZE);
		pDataToWrite[totalFileSize - CRC_SIZE] = crc;

		EncryptDecrypt(pDataToWrite.get(), totalFileSize);

		return pDataToWrite;
	}

	/**
	 * Writes the prepared data to a file.
	 *
	 * This function attempts to open a file and write the given data to it. It checks for errors during
	 * file opening and writing, ensuring that the data is written correctly to the file system.
	 *
	 * @param fileName The name of the file where data will be written.
	 * @param pData A pointer to the data to be written.
	 * @param nDataSize The size of the data to be written.
	 * @return true if the data was successfully written; false otherwise.
	 */
	bool WriteToFileOps::WriteDataFile(const char* fileName, const char* pData, size_t nDataSize) {
		if (nDataSize == 0 || !pData) {
			cerr << "Error: Invalid data size or null data pointer provided.\n";
			return false;
		}

		ofstream file(fileName, ios::binary);
		if (!file.is_open()) {
			cerr << "Error: Failed to open file '" << fileName << "' for writing.\n";
			return false;
		}

		file.write(pData, nDataSize);
		if (!file.good()) {
			cerr << "Error: Failed to write data to file '" << fileName << "'.\n";
			file.close();
			return false;
		}

		file.close();
		return true;
	}
}