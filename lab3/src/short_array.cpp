#include "short_array.hpp"
#include <algorithm>
#include <cstring>

ShortArray::ShortArray() : length(0), is_dynamic(false) {}

ShortArray::ShortArray(size_t size, short fill_value)
  : length(size), is_dynamic(size > INLINE_CAPACITY) {
  if (is_dynamic) {
    storage.heap_ptr = new short[size];
    storage.capacity = size;
    std::fill(storage.heap_ptr, storage.heap_ptr + size, fill_value);
  } else {
    std::fill(storage.inline_data, storage.inline_data + size, fill_value);
  }
}

ShortArray::ShortArray(const ShortArray& other)
  : length(other.length), is_dynamic(other.is_dynamic) {
  if (is_dynamic) {
    storage.heap_ptr = new short[other.storage.capacity];
    storage.capacity = other.storage.capacity;
    std::memcpy(storage.heap_ptr, other.storage.heap_ptr, length * sizeof(short));
  } else {
    std::memcpy(storage.inline_data, other.storage.inline_data, length * sizeof(short));
  }
}

ShortArray& ShortArray::operator=(const ShortArray& other) {
  if (this != &other) {
    if (is_dynamic) delete[] storage.heap_ptr;

    length = other.length;
    is_dynamic = other.is_dynamic;

    if (is_dynamic) {
      storage.heap_ptr = new short[other.storage.capacity];
      storage.capacity = other.storage.capacity;
      std::memcpy(storage.heap_ptr, other.storage.heap_ptr, length * sizeof(short));
    } else {
      std::memcpy(storage.inline_data, other.storage.inline_data, length * sizeof(short));
    }
  }
  return *this;
}

ShortArray::~ShortArray() {
  if (is_dynamic) delete[] storage.heap_ptr;
}

void ShortArray::ensure_capacity(size_t min_capacity) {
  if (!is_dynamic && min_capacity <= INLINE_CAPACITY)
    return;

  if (!is_dynamic) {
    // Переход из встроенного режима в динамический
    short* new_data = new short[min_capacity];
    std::memcpy(new_data, storage.inline_data, length * sizeof(short));
    storage.heap_ptr = new_data;
    storage.capacity = min_capacity;
    is_dynamic = true;
  } else if (min_capacity > storage.capacity) {
    short* new_data = new short[min_capacity];
    std::memcpy(new_data, storage.heap_ptr, length * sizeof(short));
    delete[] storage.heap_ptr;
    storage.heap_ptr = new_data;
    storage.capacity = min_capacity;
  }
}

void ShortArray::push(short value) {
  ensure_capacity(length + 1);
  if (is_dynamic)
    storage.heap_ptr[length++] = value;
  else
    storage.inline_data[length++] = value;
}

short ShortArray::pop() {
  if (length == 0) throw std::out_of_range("pop from empty array");
  return is_dynamic ? storage.heap_ptr[--length] : storage.inline_data[--length];
}

size_t ShortArray::size() const {
  return length;
}

void ShortArray::resize(size_t new_size, short fill_value) {
  ensure_capacity(new_size);
  if (new_size > length) {
    if (is_dynamic)
      std::fill(storage.heap_ptr + length, storage.heap_ptr + new_size, fill_value);
    else
      std::fill(storage.inline_data + length, storage.inline_data + new_size, fill_value);
  }
  length = new_size;
}

short& ShortArray::operator[](size_t index) {
  if (index >= length) throw std::out_of_range("Index out of range");
  return is_dynamic ? storage.heap_ptr[index] : storage.inline_data[index];
}

short ShortArray::operator[](size_t index) const {
  if (index >= length) throw std::out_of_range("Index out of range");
  return is_dynamic ? storage.heap_ptr[index] : storage.inline_data[index];
}

void ShortArray::print_debug_info() const {
  std::cout << "ShortArray(size = " << length << ", ";
  std::cout << (is_dynamic ? "dynamic" : "inline") << "): ";
  for (size_t i = 0; i < length; ++i) {
    std::cout << (*this)[i] << ' ';
  }
  std::cout << '\n';
}
