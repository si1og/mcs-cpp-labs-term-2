#pragma once
#include "circle.hpp"
#include <iostream>


class List;

class Node {
  friend class List;

private:
  Node *pPrev;
  Node *pNext;
  Circle m_Data;

public:
  Node();

  Node(Node *prev, Node *next, const Circle *pc);

  ~Node();
  friend std::ostream &operator<<(std::ostream &os, const List &list);
};
