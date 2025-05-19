#pragma once
#include "circle.hpp"
#include "node.hpp"
#include <iostream>
#include <stdexcept>

class List {
  private:
  Node *head;
  Node *tail;
  size_t m_size;
  
  public:
  List();
  ~List();
  
  void push_front(const Circle &c);
  void push_back(const Circle &c);
  void pop_front();
  void pop_back();
  size_t size() const;
  
  void clear();
  Circle &at(size_t idx);
  const Circle &at(size_t idx) const;
  Node *find(const Circle &c);
  void print(std::ostream &out) const;
  void insert(size_t idx, const Circle &c);
  void erase(size_t idx);
  void sort_by_area();
  void write_to_file(const char *filename) const;
  void read_from_file(const char *filename);
  
  friend std::ostream &operator<<(std::ostream &os, const List &list);
};
