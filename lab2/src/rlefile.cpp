#include "rlefile.hpp"

#include <iostream>
using namespace std;

RleFile::RleFile(const char* path, const char* mode)
    : BaseFile(path, mode) {
  cout << "[RleFile ctor]\n";
  if (!is_open()) std::cerr << "Файл не открылся!\n";
}

RleFile::~RleFile() {
  cout << "[RleFile dtor]\n";
}

size_t RleFile::write(const MyString& str) {
    MyString encoded_str = encode(str);
    return BaseFile::write(encoded_str.get_data(), encoded_str.get_length());
}

size_t RleFile::write(const void* buf, size_t n_bytes) {
  if (!is_open()) {
    cerr << "[RleFile::write] Файл не открыт!\n";
    return 0;
  }

  MyString temp(reinterpret_cast<const char*>(buf));
  MyString encoded = encode(temp);

  return BaseFile::write(encoded.get_data(), encoded.get_length());
}

MyString RleFile::read(size_t max_bytes) {
    char* buffer = new char[max_bytes + 1];
    size_t bytes_read = BaseFile::read(buffer, max_bytes);
    buffer[bytes_read] = '\0';

    MyString encoded_str(buffer);
    delete[] buffer;

    return decode(encoded_str);
}

MyString RleFile::encode(const MyString& input) {
    MyString result;

    int len = input.get_length();
    for (int i = 0; i < len; ++i) {
        char current = input.get(i);
        int count = 1;

        while (i + 1 < len && input.get(i + 1) == current) {
            count++;
            i++;
        }

        result.append(current);
        result.append((char)count);
    }

    return result;
}

MyString RleFile::decode(const MyString& input) {
    MyString result;

    int len = input.get_length();
    for (int i = 0; i < len; i += 2) {
        char current = input.get(i);
        int count = (unsigned char)input.get(i + 1);

        for (int j = 0; j < count; ++j) {
            result.append(current);
        }
    }

    return result;
}