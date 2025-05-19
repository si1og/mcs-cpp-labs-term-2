#include "node.hpp"

Node::Node() : pPrev(nullptr), pNext(nullptr), m_Data() {}

Node::Node(Node *prev, Node *next, const Circle *pc)
    : pPrev(prev), pNext(next), m_Data(*pc) {}

Node::~Node() {}
