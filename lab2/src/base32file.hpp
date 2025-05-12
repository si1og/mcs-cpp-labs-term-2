#pragma once
#include "basefile.hpp"
#include "my-string.hpp"

class Base32File : public BaseFile {
private:
    MyString encode_table;

public:
    Base32File(const char* path, const char* mode, const MyString& table = MyString("ABCDEFGHIJKLMNOPQRSTUVWXYZ123456"));
    ~Base32File();

    size_t write(const void* buf, size_t n_bytes) override;

    size_t write(const MyString& data);
    MyString read();

private:
    int encode32(const MyString& raw_data, MyString& dst);
    int decode32(const MyString& encoded_data, MyString& dst);
};
