#include "bool_array.hpp"
#include <cstring>
#include <stdexcept>

using namespace std;

BoolArray::BoolArray(size_t size, bool value) : bit_count(size) {
  byte_count = (size + 7) / 8;
  data = new byte[byte_count];
  memset(data, value ? 0xFF : 0x00, byte_count);
}

BoolArray::BoolArray(const BoolArray& other) : byte_count(other.byte_count), bit_count(other.bit_count) {
  data = new byte[byte_count];
  memcpy(data, other.data, byte_count);
}

BoolArray& BoolArray::operator=(const BoolArray& other) {
  if (this != &other) {
    delete[] data;
    byte_count = other.byte_count;
    bit_count = other.bit_count;
    data = new byte[byte_count];
    memcpy(data, other.data, byte_count);
  }
  return *this;
}

BoolArray::~BoolArray() {
  delete[] data;
}

BoolProxy BoolArray::operator[](size_t index) {
  if (index >= bit_count) throw out_of_range("index out of range");
  return BoolProxy(data[index / 8], 1 << (index % 8));
}

bool BoolArray::operator[](size_t index) const {
  return get_bit(index);
}

void BoolArray::resize(size_t new_size, bool value) {
  size_t new_byte_count = (new_size + 7) / 8;
  byte* new_data = new byte[new_byte_count];
  std::memset(new_data, value ? 0xFF : 0x00, new_byte_count);

  size_t old_byte_count = (bit_count + 7) / 8;

  size_t bytes_to_copy = (new_byte_count < old_byte_count) ? new_byte_count : old_byte_count;
  std::memcpy(new_data, data, bytes_to_copy);

  if (bit_count % 8 != 0 && value && new_size > bit_count) {
    uint8_t mask = (1 << (bit_count % 8)) - 1;
    new_data[bytes_to_copy - 1] |= ~mask;
  }

  delete[] data;
  data = new_data;
  byte_count = new_byte_count;
  bit_count = new_size;

  if (bit_count % 8 != 0) {
    uint8_t mask = (1 << (bit_count % 8)) - 1;
    data[byte_count - 1] &= mask | (value ? ~mask : 0x00);
  }
}


bool BoolArray::get_bit(size_t index) const {
  if (index >= bit_count) throw out_of_range("index out of range");
  return (data[index / 8] >> (index % 8)) & 1;
}
