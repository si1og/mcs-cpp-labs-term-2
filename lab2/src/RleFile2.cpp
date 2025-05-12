#include "RleFile2.hpp"
#include <iostream>

RleFile2::RleFile2(IFile* file)
  : inner(file) {
  std::cout << "[RleFile2 ctor]\n";
}

RleFile2::~RleFile2() {
  std::cout << "[RleFile2 dtor]\n";
  delete inner;
}

bool RleFile2::can_read() const {
  return inner->can_read();
}

bool RleFile2::can_write() const {
  return inner->can_write();
}

size_t RleFile2::write(const void* buf, size_t n_bytes) {
  MyString temp(reinterpret_cast<const char*>(buf));
  MyString encoded = encode(temp);

  return inner->write(encoded.get_data(), encoded.get_length());
}

size_t RleFile2::read(void* buf, size_t max_bytes) {
  return inner->read(buf, max_bytes);
}

MyString RleFile2::encode(const MyString& input) {
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

