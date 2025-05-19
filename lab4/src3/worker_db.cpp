#include "worker_db.hpp"
#include <cstring>

WorkerDb::WorkerDb() : entries(nullptr), size(0), capacity(0) {}

WorkerDb::~WorkerDb() {
  delete[] entries;
}

WorkerDb::WorkerDb(const WorkerDb& other) : size(other.size), capacity(other.capacity) {
  entries = new Entry[capacity];
  for (size_t i = 0; i < size; ++i) {
    entries[i] = other.entries[i];
  }
}

WorkerDb& WorkerDb::operator=(const WorkerDb& other) {
  if (this == &other) return *this;

  delete[] entries;
  size = other.size;
  capacity = other.capacity;
  entries = new Entry[capacity];
  for (size_t i = 0; i < size; ++i) {
    entries[i] = other.entries[i];
  }

  return *this;
}

void WorkerDb::ensure_capacity(size_t min_capacity) {
  if (capacity >= min_capacity) return;
  size_t new_capacity = capacity ? capacity * 2 : 4;
  if (new_capacity < min_capacity) new_capacity = min_capacity;

  Entry* new_entries = new Entry[new_capacity];
  for (size_t i = 0; i < size; ++i)
    new_entries[i] = entries[i];

  delete[] entries;
  entries = new_entries;
  capacity = new_capacity;
}

WorkerData& WorkerDb::operator[](const MyString& key) {
  for (size_t i = 0; i < size; ++i) {
    if (entries[i].key == key) {
      return entries[i].value;
    }
  }

  ensure_capacity(size + 1);
  entries[size].key = key;
  entries[size].value = WorkerData();
  return entries[size++].value;
}

WorkerDb::Iterator WorkerDb::begin() {
  return Iterator(entries);
}

WorkerDb::Iterator WorkerDb::end() {
  return Iterator(entries + size);
}