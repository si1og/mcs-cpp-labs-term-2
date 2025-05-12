#pragma once
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <cstring>

class ShortArray {
private:
  static constexpr uintptr_t FLAG_MASK = 1;

  uintptr_t ptr_with_flag;
  size_t size;
  size_t capacity;

  static constexpr size_t INLINE_CAPACITY =
    (sizeof(ptr_with_flag) + sizeof(size_t) * 2) / sizeof(short);
  alignas(short) short inline_data[INLINE_CAPACITY];

  bool is_inline() const;
  short* data_ptr() const;
  void set_data_ptr(short* ptr, bool use_inline);
  void ensure_capacity(size_t min_capacity);

public:
  ShortArray();
  ShortArray(size_t size, short fill_value = 0);
  ShortArray(const ShortArray& other);
  ShortArray& operator=(const ShortArray& other);
  ~ShortArray();

  void push(short value);
  short pop();
  void resize(size_t new_size, short fill_value = 0);
  size_t size_() const;

  short& operator[](size_t index);
  short operator[](size_t index) const;

  void print_debug() const;
};
