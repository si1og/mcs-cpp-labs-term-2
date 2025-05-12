#include "short_array.hpp"

bool ShortArray::is_inline() const {
  return ptr_with_flag & FLAG_MASK;
}

short* ShortArray::data_ptr() const {
  if (is_inline()) return const_cast<short*>(inline_data);
  return reinterpret_cast<short*>(ptr_with_flag & ~FLAG_MASK);
}

void ShortArray::set_data_ptr(short* ptr, bool use_inline) {
  if (use_inline)
    ptr_with_flag = reinterpret_cast<uintptr_t>(inline_data) | FLAG_MASK;
  else
    ptr_with_flag = reinterpret_cast<uintptr_t>(ptr) & ~FLAG_MASK;
}

ShortArray::ShortArray() {
  set_data_ptr(inline_data, true);
  size = 0;
}

ShortArray::ShortArray(size_t new_size, short fill_value) {
  if (new_size <= INLINE_CAPACITY) {
    set_data_ptr(inline_data, true);
    size = new_size;
    std::fill(inline_data, inline_data + new_size, fill_value);
  } else {
    short* heap_data = new short[new_size];
    set_data_ptr(heap_data, false);
    size = new_size;
    capacity = new_size;
    std::fill(heap_data, heap_data + new_size, fill_value);
  }
}

ShortArray::ShortArray(const ShortArray& other) {
  if (other.is_inline()) {
    set_data_ptr(inline_data, true);
    size = other.size;
    std::memcpy(inline_data, other.inline_data, sizeof(short) * size);
  } else {
    short* heap_data = new short[other.capacity];
    set_data_ptr(heap_data, false);
    size = other.size;
    capacity = other.capacity;
    std::memcpy(heap_data, other.data_ptr(), sizeof(short) * size);
  }
}

ShortArray& ShortArray::operator=(const ShortArray& other) {
  if (this == &other) return *this;

  if (!is_inline()) delete[] data_ptr();

  if (other.is_inline()) {
    set_data_ptr(inline_data, true);
    size = other.size;
    std::memcpy(inline_data, other.inline_data, sizeof(short) * size);
  } else {
    short* heap_data = new short[other.capacity];
    set_data_ptr(heap_data, false);
    size = other.size;
    capacity = other.capacity;
    std::memcpy(heap_data, other.data_ptr(), sizeof(short) * size);
  }

  return *this;
}

ShortArray::~ShortArray() {
  if (!is_inline()) delete[] data_ptr();
}

void ShortArray::ensure_capacity(size_t min_capacity) {
  if (is_inline() && min_capacity <= INLINE_CAPACITY) return;

  if (is_inline()) {
    short* new_data = new short[min_capacity];
    std::memcpy(new_data, inline_data, sizeof(short) * size);
    set_data_ptr(new_data, false);
    capacity = min_capacity;
  } else if (min_capacity > capacity) {
    short* new_data = new short[min_capacity];
    std::memcpy(new_data, data_ptr(), sizeof(short) * size);
    delete[] data_ptr();
    set_data_ptr(new_data, false);
    capacity = min_capacity;
  }
}

void ShortArray::push(short value) {
  ensure_capacity(size + 1);
  data_ptr()[size++] = value;
}

short ShortArray::pop() {
  if (size == 0) throw std::out_of_range("pop from empty array");
  return data_ptr()[--size];
}

void ShortArray::resize(size_t new_size, short fill_value) {
  ensure_capacity(new_size);
  if (new_size > size)
    std::fill(data_ptr() + size, data_ptr() + new_size, fill_value);
  size = new_size;
}

size_t ShortArray::size_() const {
  return size;
}

short& ShortArray::operator[](size_t index) {
  if (index >= size) throw std::out_of_range("index out of range");
  return data_ptr()[index];
}

short ShortArray::operator[](size_t index) const {
  if (index >= size) throw std::out_of_range("index out of range");
  return data_ptr()[index];
}

void ShortArray::print_debug() const {
  std::cout << "ShortArray(size = " << size << ", "
            << (is_inline() ? "inline" : "dynamic") << "): ";
  for (size_t i = 0; i < size; ++i)
    std::cout << (*this)[i] << ' ';
  std::cout << "\n";
}
