#pragma once
#include <cstddef>
#include <cstdint>
#include <iostream>

class BoolArray {
public:
  class BoolProxy {
    uint8_t &byte;
    uint8_t mask;

  public:
    BoolProxy(uint8_t &b, uint8_t m) : byte(b), mask(m) {}
    operator bool() const { return byte & mask; }
    BoolProxy &operator=(bool value) {
      if (value)
        byte |= mask;
      else
        byte &= ~mask;
      return *this;
    }
  };

private:
  uint8_t *data;
  size_t count;

public:
  BoolArray(size_t size, bool value = false);
  BoolArray(const BoolArray &other);
  BoolArray &operator=(const BoolArray &other);
  ~BoolArray();

  void resize(size_t new_size, bool value = false);

  size_t size() const { return count; }
  BoolProxy operator[](size_t index);
  bool operator[](size_t index) const;
};
