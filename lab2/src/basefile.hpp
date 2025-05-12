#pragma once
#include <cstdio>
#include "IFile.hpp"

class BaseFile : public IFile {
private:
    FILE* file;

public:
    BaseFile();
    BaseFile(const char* path, const char* mode);
    BaseFile(FILE* existing_file);
    virtual ~BaseFile();

    bool is_open() const;

    bool can_read() const override;
    bool can_write() const override;

    size_t write_raw(const void* buf, size_t n_bytes);
    size_t read_raw(void* buf, size_t max_bytes);

    long tell() const;
    bool seek(long offset);

    size_t write(const void* buf, size_t n_bytes) override;
    size_t read(void* buf, size_t max_bytes) override;
};
