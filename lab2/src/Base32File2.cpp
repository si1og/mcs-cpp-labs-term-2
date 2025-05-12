#include "Base32File2.hpp"
#include <iostream>

Base32File2::Base32File2(IFile* file)
  : inner(file), encode_table("ABCDEFGHIJKLMNOPQRSTUVWXYZ123456") {
  std::cout << "[Base32File2 ctor]\n";
}

Base32File2::~Base32File2() {
  std::cout << "[Base32File2 dtor]\n";
  delete inner;
}

bool Base32File2::can_read() const {
  return inner->can_read();
}

bool Base32File2::can_write() const {
  return inner->can_write();
}

size_t Base32File2::write(const void* buf, size_t n_bytes) {
  MyString temp(reinterpret_cast<const char*>(buf));
  MyString encoded;
  encode32(temp, encoded);

  return inner->write(encoded.get_data(), encoded.get_length());
}

size_t Base32File2::read(void* buf, size_t max_bytes) {
  return inner->read(buf, max_bytes);
}

int Base32File2::encode32(const MyString& raw_data, MyString& dst) {
  int buffer = 0, bitsLeft = 0;

  for (int i = 0; i < raw_data.get_length(); ++i) {
    buffer = (buffer << 8) | (unsigned char)raw_data.get(i);
    bitsLeft += 8;

    while (bitsLeft >= 5) {
      bitsLeft -= 5;
      dst.append(encode_table.get((buffer >> bitsLeft) & 0x1F));
    }
  }

  if (bitsLeft > 0) {
    dst.append(encode_table.get((buffer << (5 - bitsLeft)) & 0x1F));
  }

  return 0;
}

