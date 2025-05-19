#pragma once
#include <cstddef>
#include <iostream>
#include <cstring>
#include <cassert>
#include <cstdint>

class ShortArray {
private:
  static const size_t INLINE_CAP = 12;
  union Storage {
    struct {
      short* ptr;
      size_t size;
      size_t cap;
    } dyn;
    short inl[INLINE_CAP];
    // Инициализирует всё 0
    Storage() { std::memset(this, 0, sizeof(Storage)); }
  } storage;

  // Флаг хранится в старшем бите cap
  static constexpr size_t FLAG = size_t(1) << (sizeof(size_t) * 8 - 1);

  bool is_dynamic() const { return storage.dyn.cap & FLAG; }
  void set_dynamic(bool val) {
    if (val) storage.dyn.cap |= FLAG;
    else storage.dyn.cap &= ~FLAG;
  }
  size_t pure_cap() const { return storage.dyn.cap & ~FLAG; }

public:
  ShortArray();
  ShortArray(size_t n, short fill_value = 0);
  ShortArray(const ShortArray& other);
  ShortArray& operator=(const ShortArray& other);
  ShortArray(ShortArray&& other) noexcept;
  ShortArray& operator=(ShortArray&& other) noexcept;
  ~ShortArray();

  size_t size() const;
  void resize(size_t new_size, short fill_value = 0);
  void push(short val);
  short pop();
  short& operator[](size_t idx);
  const short& operator[](size_t idx) const;
  void print() const;
};
