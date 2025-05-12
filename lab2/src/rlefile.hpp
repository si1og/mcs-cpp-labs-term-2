#pragma once
#include "basefile.hpp"
#include "my-string.hpp"

class RleFile : public BaseFile {
public:
    RleFile(const char* path, const char* mode);
    ~RleFile();

    size_t write(const void* buf, size_t n_bytes) override;

    size_t write(const MyString& str);
    MyString read(size_t max_bytes);

private:
    MyString encode(const MyString& input);
    MyString decode(const MyString& input);
};