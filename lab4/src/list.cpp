#include "list.hpp"
#include "node.hpp"
#include <fstream>

List::List() : m_size(0) {
  head = new Node();
  tail = new Node();
  head->pNext = tail;
  tail->pPrev = head;
}

List::~List() {
  Node *cur = head->pNext;
  while (cur != tail) {
    Node *to_delete = cur;
    cur = cur->pNext;
    delete to_delete;
  }
  delete head;
  delete tail;
}

void List::push_front(const Circle &c) {
  Node *node = new Node(head, head->pNext, &c);
  head->pNext->pPrev = node;
  head->pNext = node;
  ++m_size;
}

void List::push_back(const Circle &c) {
  Node *node = new Node(tail->pPrev, tail, &c);
  tail->pPrev->pNext = node;
  tail->pPrev = node;
  ++m_size;
}

void List::pop_front() {
  if (head->pNext == tail)
    return;
  Node *node = head->pNext;
  head->pNext = node->pNext;
  node->pNext->pPrev = head;
  delete node;
  --m_size;
}

void List::pop_back() {
  if (tail->pPrev == head)
    return;
  Node *node = tail->pPrev;
  tail->pPrev = node->pPrev;
  node->pPrev->pNext = tail;
  delete node;
  --m_size;
}

size_t List::size() const { return m_size; }

void List::clear() {
  Node *cur = head->pNext;
  while (cur != tail) {
    Node *to_delete = cur;
    cur = cur->pNext;
    delete to_delete;
  }
  head->pNext = tail;
  tail->pPrev = head;
  m_size = 0;
}

Circle &List::at(size_t idx) {
  if (idx >= m_size)
    throw std::out_of_range("Index out of range");
  Node *cur = head->pNext;
  for (size_t i = 0; i < idx; ++i)
    cur = cur->pNext;
  return cur->m_Data;
}

const Circle &List::at(size_t idx) const {
  if (idx >= m_size)
    throw std::out_of_range("Index out of range");
  Node *cur = head->pNext;
  for (size_t i = 0; i < idx; ++i)
    cur = cur->pNext;
  return cur->m_Data;
}

Node *List::find(const Circle &c) {
  Node *cur = head->pNext;
  while (cur != tail) {
    if (cur->m_Data.get_center() == c.get_center() &&
        cur->m_Data.get_radius() == c.get_radius())
      return cur;
    cur = cur->pNext;
  }
  return nullptr;
}

void List::print(std::ostream &out) const {
  Node *cur = head->pNext;
  int idx = 0;
  while (cur != tail) {
    out << "Circle " << idx++ << ": Center(" << cur->m_Data.get_center().get_x()
        << ", " << cur->m_Data.get_center().get_y() << "), "
        << "Radius: " << cur->m_Data.get_radius() << "\n";
    cur = cur->pNext;
  }
}

void List::insert(size_t idx, const Circle &c) {
  if (idx > m_size)
    throw std::out_of_range("Index out of range (insert)");
  Node *cur = head;
  // после этого цикла cur будет указывать на узел, _перед_ которым надо
  // вставлять
  for (size_t i = 0; i < idx; ++i)
    cur = cur->pNext;
  // cur->pNext — это тот элемент, который станет следующим после вставленного
  Node *next_node = cur->pNext;
  Node *node = new Node(cur, next_node, &c);
  cur->pNext = node;
  next_node->pPrev = node;
  ++m_size;
}

void List::erase(size_t idx) {
  if (idx >= m_size)
    throw std::out_of_range("Index out of range (erase)");
  Node *cur = head->pNext;
  for (size_t i = 0; i < idx; ++i)
    cur = cur->pNext;
  // cur — это удаляемый элемент
  cur->pPrev->pNext = cur->pNext;
  cur->pNext->pPrev = cur->pPrev;
  delete cur;
  --m_size;
}

void List::sort_by_area() {
  if (m_size < 2)
    return;
  bool swapped;
  do {
    swapped = false;
    Node *curr = head->pNext;
    while (curr->pNext != tail) {
      if (curr->m_Data.area() > curr->pNext->m_Data.area()) {
        std::swap(curr->m_Data, curr->pNext->m_Data);
        swapped = true;
      }
      curr = curr->pNext;
    }
  } while (swapped);
}

std::ostream &operator<<(std::ostream &os, const List &list) {
  int idx = 0;
  for (Node *node = list.head->pNext; node != list.tail;
       node = node->pNext, ++idx) {
    os << idx << ") Center: (" << node->m_Data.get_center().get_x() << ", "
       << node->m_Data.get_center().get_y() << "), "
       << "Radius: " << node->m_Data.get_radius()
       << ", Area: " << node->m_Data.area() << "\n";
  }
  return os;
}

void List::write_to_file(const char *filename) const {
  std::ofstream fout(filename);
  if (!fout)
    throw std::runtime_error("Can't open file for writing!");
  Node* cur = head->pNext;
  while (cur != tail) {
    Point c = cur->m_Data.get_center();
    fout << c.get_x() << " " << c.get_y() << " " << cur->m_Data.get_radius() << "\n";
    cur = cur->pNext;
  }
  fout.close();
}


void List::read_from_file(const char *filename) {
  std::ifstream fin(filename);
  if (!fin)
    throw std::runtime_error("Can't open file for reading!");
  clear();
  double x, y, r;
  while (fin >> x >> y >> r) {
    push_back(Circle(Point(x, y), r));
  }
  fin.close();
}
