#include "bool_array.hpp"
#include <cstring>
#include <stdexcept>

BoolArray::BoolArray(size_t size, bool value) : count(size) {
  size_t bytes = (size + 7) / 8;
  data = new uint8_t[bytes];
  std::memset(data, value ? 0xFF : 0x00, bytes);
}

BoolArray::BoolArray(const BoolArray &other) : count(other.count) {
  size_t bytes = (count + 7) / 8;
  data = new uint8_t[bytes];
  std::memcpy(data, other.data, bytes);
}

BoolArray &BoolArray::operator=(const BoolArray &other) {
  if (this != &other) {
    delete[] data;
    count = other.count;
    size_t bytes = (count + 7) / 8;
    data = new uint8_t[bytes];
    std::memcpy(data, other.data, bytes);
  }
  return *this;
}

BoolArray::~BoolArray() {
  delete[] data;
}

BoolArray::BoolProxy BoolArray::operator[](size_t index) {
  if (index >= count) throw std::out_of_range("Index out of range");
  return BoolProxy(data[index / 8], 1 << (index % 8));
}

bool BoolArray::operator[](size_t index) const {
  if (index >= count) throw std::out_of_range("Index out of range");
  return (data[index / 8] >> (index % 8)) & 1;
}

void BoolArray::resize(size_t new_size, bool value) {
  size_t new_bytes = (new_size + 7) / 8;
  size_t old_bytes = (count + 7) / 8;

  uint8_t *new_data = new uint8_t[new_bytes];
  std::memset(new_data, value ? 0xFF : 0x00, new_bytes);

  size_t min_bytes = (count < new_size ? old_bytes : new_bytes);
  std::memcpy(new_data, data, min_bytes);

  delete[] data;
  data = new_data;
  count = new_size;
}
