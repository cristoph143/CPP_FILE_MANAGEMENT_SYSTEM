#pragma once

#include <string>
#include <vector>
#include <memory>

constexpr int DEBUG = 1;
constexpr size_t BUFFER_SIZE = 1024;
constexpr unsigned char FILEID = 0xFA;
constexpr size_t HEADER_SIZE = 2;
constexpr size_t CRC_SIZE = 1;
constexpr int MAXFILE_COUNT = 3;
constexpr char FILE_FOLDER[] = "files";

using namespace std;

struct HeaderInfo {
    unsigned char fileID;
    unsigned char readCount;
    unsigned crc;
    unique_ptr<unsigned char[]> payload;
    size_t payloadSize;

    HeaderInfo() : fileID(0), readCount(0), crc(0), payloadSize(0), payload(nullptr) {}
};

struct DataBlock {
    const char* data;
    size_t size;
};

struct Accumulator {
    char* data;
    size_t size;
    size_t capacity;

    Accumulator() : data(nullptr), size(0), capacity(0) {}
    ~Accumulator() {
        delete[] data;
    }
};

#if DEBUG
#define DEBUG_PRINT(fmt, ...) fprintf(stderr, (fmt), ##__VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...)
#endif