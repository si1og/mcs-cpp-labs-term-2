#include "base32file.hpp"

#include <iostream>
using namespace std;

Base32File::Base32File(const char* path, const char* mode, const MyString& table)
  : BaseFile(path, mode), encode_table(table) {
    std::cout << "[Base32File ctor]\n";
    if (!is_open()) std::cerr << "Файл не открылся!\n";
  }

Base32File::~Base32File() {
  std::cout << "[Base32File dtor]\n";
}

size_t Base32File::write(const MyString& data) {
  MyString encoded_data;
  encode32(data, encoded_data);

  int encoded_length = encoded_data.get_length();

  BaseFile::write(&encoded_length, sizeof(encoded_length));
  return BaseFile::write(encoded_data.get_data(), encoded_length);
}

size_t Base32File::write(const void* buf, size_t n_bytes) {
  if (!is_open()) {
    cerr << "[Base32File::write] Файл не открыт!\n";
    return 0;
  }

  MyString temp(reinterpret_cast<const char*>(buf));
  MyString encoded;
  encode32(temp, encoded);

  return BaseFile::write(encoded.get_data(), encoded.get_length());
}

MyString Base32File::read() {
  int encoded_length = 0;
  if (BaseFile::read(&encoded_length, sizeof(encoded_length)) != sizeof(encoded_length)) {
      return MyString();
  }

  char* buffer = new char[encoded_length + 1];
  size_t bytes_read = BaseFile::read(buffer, encoded_length);
  buffer[bytes_read] = '\0';

  MyString encoded_data(buffer);
  delete[] buffer;

  MyString decoded_data;
  decode32(encoded_data, decoded_data);

  return decoded_data;
}

int Base32File::encode32(const MyString& raw_data, MyString& dst) {
    int bit_buffer = 0, bit_count = 0;

    for (int i = 0; i < raw_data.get_length(); ++i) {
        bit_buffer = (bit_buffer << 8) | (unsigned char)raw_data.get(i);
        bit_count += 8;

        while (bit_count >= 5) {
            bit_count -= 5;
            dst.append(encode_table.get((bit_buffer >> bit_count) & 0x1F));
        }
    }

    if (bit_count > 0) {
        dst.append(encode_table.get((bit_buffer << (5 - bit_count)) & 0x1F));
    }

    return 0;
}

int Base32File::decode32(const MyString& encoded_data, MyString& dst) {
    int decode_table[256];
    for (int i = 0; i < 256; ++i) decode_table[i] = -1;
    for (int i = 0; i < encode_table.get_length(); ++i)
        decode_table[(unsigned char)encode_table.get(i)] = i;

    int bit_buffer = 0, bit_count = 0;

    for (int i = 0; i < encoded_data.get_length(); ++i) {
        int val = decode_table[(unsigned char)encoded_data.get(i)];
        if (val == -1) return 2;

        bit_buffer = (bit_buffer << 5) | val;
        bit_count += 5;

        if (bit_count >= 8) {
            bit_count -= 8;
            dst.append((char)((bit_buffer >> bit_count) & 0xFF));
        }
    }

    return 0;
}
