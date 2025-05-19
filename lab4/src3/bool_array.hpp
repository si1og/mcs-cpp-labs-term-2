#pragma once
#include <cstddef>
#include <cstdint>

class BoolProxy;

class BoolArray {
public:
  BoolArray(size_t size = 0, bool value = false);
  BoolArray(const BoolArray& other);
  BoolArray& operator=(const BoolArray& other);
  ~BoolArray();

  BoolProxy operator[](size_t index);
  bool operator[](size_t index) const;

  void resize(size_t new_size, bool value = false);
  size_t size() const { return bit_count; }

private:
  using byte = uint8_t;
  byte* data = nullptr;
  size_t byte_count = 0;
  size_t bit_count = 0;

  void set_bit(size_t index, bool value);
  bool get_bit(size_t index) const;
};

class BoolProxy {
  friend class BoolArray;
  uint8_t& byte;
  uint8_t mask;

  BoolProxy(uint8_t& byte, uint8_t mask) : byte(byte), mask(mask) {}

public:
  BoolProxy& operator=(bool value) {
    if (value) byte |= mask;
    else byte &= ~mask;
    return *this;
  }

  BoolProxy& operator=(const BoolProxy& other) {
    return *this = static_cast<bool>(other);
  }

  operator bool() const {
    return (byte & mask) != 0;
  }
};
