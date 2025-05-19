#include "short_array.hpp"

ShortArray::ShortArray() {
  set_dynamic(false);
  storage.dyn.size = 0;
}

ShortArray::ShortArray(size_t n, short fill) {
  if (n > INLINE_CAP) {
    storage.dyn.ptr = new short[n];
    storage.dyn.size = n;
    storage.dyn.cap = n;
    set_dynamic(true);
    for (size_t i = 0; i < n; ++i)
      storage.dyn.ptr[i] = fill;
  } else {
    set_dynamic(false);
    storage.dyn.size = n;
    for (size_t i = 0; i < n; ++i)
      storage.inl[i] = fill;
  }
}

ShortArray::ShortArray(const ShortArray& o) {
  if (o.is_dynamic()) {
    storage.dyn.ptr = new short[o.storage.dyn.size];
    storage.dyn.size = o.storage.dyn.size;
    storage.dyn.cap = o.storage.dyn.size;
    set_dynamic(true);
    for (size_t i = 0; i < o.storage.dyn.size; ++i)
      storage.dyn.ptr[i] = o.storage.dyn.ptr[i];
  } else {
    set_dynamic(false);
    storage.dyn.size = o.storage.dyn.size;
    for (size_t i = 0; i < o.storage.dyn.size; ++i)
      storage.inl[i] = o.storage.inl[i];
  }
}

ShortArray& ShortArray::operator=(const ShortArray& o) {
  if (this == &o) return *this;
  if (is_dynamic()) delete[] storage.dyn.ptr;
  if (o.is_dynamic()) {
    storage.dyn.ptr = new short[o.storage.dyn.size];
    storage.dyn.size = o.storage.dyn.size;
    storage.dyn.cap = o.storage.dyn.size;
    set_dynamic(true);
    for (size_t i = 0; i < o.storage.dyn.size; ++i)
      storage.dyn.ptr[i] = o.storage.dyn.ptr[i];
  } else {
    set_dynamic(false);
    storage.dyn.size = o.storage.dyn.size;
    for (size_t i = 0; i < o.storage.dyn.size; ++i)
      storage.inl[i] = o.storage.inl[i];
  }
  return *this;
}

ShortArray::ShortArray(ShortArray&& o) noexcept {
  if (o.is_dynamic()) {
    storage.dyn.ptr = o.storage.dyn.ptr;
    storage.dyn.size = o.storage.dyn.size;
    storage.dyn.cap = o.storage.dyn.cap;
    o.storage.dyn.ptr = nullptr;
    o.storage.dyn.size = 0;
    o.storage.dyn.cap = 0;
  } else {
    set_dynamic(false);
    storage.dyn.size = o.storage.dyn.size;
    for (size_t i = 0; i < o.storage.dyn.size; ++i)
      storage.inl[i] = o.storage.inl[i];
  }
}

ShortArray& ShortArray::operator=(ShortArray&& o) noexcept {
  if (this == &o) return *this;
  if (is_dynamic()) delete[] storage.dyn.ptr;
  if (o.is_dynamic()) {
    storage.dyn.ptr = o.storage.dyn.ptr;
    storage.dyn.size = o.storage.dyn.size;
    storage.dyn.cap = o.storage.dyn.cap;
    o.storage.dyn.ptr = nullptr;
    o.storage.dyn.size = 0;
    o.storage.dyn.cap = 0;
  } else {
    set_dynamic(false);
    storage.dyn.size = o.storage.dyn.size;
    for (size_t i = 0; i < o.storage.dyn.size; ++i)
      storage.inl[i] = o.storage.inl[i];
  }
  return *this;
}

ShortArray::~ShortArray() {
  if (is_dynamic())
    delete[] storage.dyn.ptr;
}

size_t ShortArray::size() const {
  return storage.dyn.size;
}

void ShortArray::resize(size_t new_size, short fill) {
  size_t old_size = storage.dyn.size;
  if (!is_dynamic() && new_size <= INLINE_CAP) {
    if (new_size > old_size) {
      for (size_t i = old_size; i < new_size; ++i)
        storage.inl[i] = fill;
    }
    storage.dyn.size = new_size;
    return;
  }
  if (!is_dynamic()) {
    short* newdata = new short[new_size];
    for (size_t i = 0; i < old_size; ++i)
      newdata[i] = storage.inl[i];
    for (size_t i = old_size; i < new_size; ++i)
      newdata[i] = fill;
    storage.dyn.ptr = newdata;
    storage.dyn.size = new_size;
    storage.dyn.cap = new_size;
    set_dynamic(true);
    return;
  }
  // dynamic
  if (new_size <= INLINE_CAP) {
    short tmp[INLINE_CAP];
    for (size_t i = 0; i < new_size && i < old_size; ++i)
      tmp[i] = storage.dyn.ptr[i];
    for (size_t i = old_size; i < new_size; ++i)
      tmp[i] = fill;
    delete[] storage.dyn.ptr;
    set_dynamic(false);
    storage.dyn.size = new_size;
    for (size_t i = 0; i < new_size; ++i)
      storage.inl[i] = tmp[i];
    return;
  }
  if (new_size > pure_cap()) {
    short* newdata = new short[new_size];
    for (size_t i = 0; i < old_size; ++i)
      newdata[i] = storage.dyn.ptr[i];
    for (size_t i = old_size; i < new_size; ++i)
      newdata[i] = fill;
    delete[] storage.dyn.ptr;
    storage.dyn.ptr = newdata;
    storage.dyn.cap = new_size;
    set_dynamic(true);
  } else {
    for (size_t i = old_size; i < new_size; ++i)
      storage.dyn.ptr[i] = fill;
  }
  storage.dyn.size = new_size;
}

void ShortArray::push(short val) {
  resize(size() + 1, val);
}

short ShortArray::pop() {
  if (size() == 0) throw std::out_of_range("pop empty");
  short res = (*this)[size()-1];
  resize(size()-1);
  return res;
}

short& ShortArray::operator[](size_t idx) {
  return is_dynamic() ? storage.dyn.ptr[idx] : storage.inl[idx];
}
const short& ShortArray::operator[](size_t idx) const {
  return is_dynamic() ? storage.dyn.ptr[idx] : storage.inl[idx];
}

void ShortArray::print() const {
  std::cout << "[";
  for (size_t i = 0; i < size(); ++i) {
    if (i > 0) std::cout << ", ";
    std::cout << (*this)[i];
  }
  std::cout << "]\n";
}
