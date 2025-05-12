#pragma once
#include <cstddef>
#include <stdexcept>
#include <iostream>

class ShortArray {
private:
  static const size_t INLINE_CAPACITY = (sizeof(short*) + sizeof(size_t)) / sizeof(short);

  union Storage {
    struct {
      short* heap_ptr;
      size_t capacity;
    };
    short inline_data[INLINE_CAPACITY];

    Storage() : heap_ptr(nullptr), capacity(0) {}
  } storage;

  size_t length;
  bool is_dynamic;

  void ensure_capacity(size_t min_capacity);

public:
  ShortArray();
  ShortArray(size_t size, short fill_value = 0);
  ShortArray(const ShortArray& other);
  ShortArray& operator=(const ShortArray& other);
  ~ShortArray();

  void push(short value);
  short pop();
  size_t size() const;
  void resize(size_t new_size, short fill_value = 0);

  short& operator[](size_t index);
  short operator[](size_t index) const;

  void print_debug_info() const;
};
