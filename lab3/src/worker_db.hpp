#pragma once
#include "my-string.hpp"
#include "worker_data.hpp"

class WorkerDb {
private:
  struct Entry {
    MyString key;
    WorkerData value;
  };

  Entry* entries;
  size_t size;
  size_t capacity;

  void ensure_capacity(size_t min_capacity);

public:
  WorkerDb();
  ~WorkerDb();
  WorkerDb(const WorkerDb& other);
  WorkerDb& operator=(const WorkerDb& other);

  WorkerData& operator[](const MyString& key);

  class Iterator {
    private:
      Entry* ptr;

    public:
      Iterator(Entry* p) : ptr(p) {}

      WorkerData& operator*() { return ptr->value; }
      WorkerData* operator->() { return &ptr->value; }

      Iterator& operator++() { ++ptr; return *this; }         // Префикс
      Iterator operator++(int) { Iterator tmp = *this; ++ptr; return tmp; } // Постфикс

      bool operator==(const Iterator& other) const { return ptr == other.ptr; }
      bool operator!=(const Iterator& other) const { return ptr != other.ptr; }

      const MyString& key() const { return ptr->key; }
    };

  Iterator begin();
  Iterator end();
};
