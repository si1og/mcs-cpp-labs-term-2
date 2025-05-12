#include "my-string.hpp"
#include <cstring>
#include <iostream>

using namespace std;

MyString::MyString() : data(nullptr), length(0) {
  // cout << "[MyString ctor default]\n";
  data = new char[1];
  data[0] = '\0';
}

MyString::MyString(const char* str) {
  // cout << "[MyString ctor(const char*)]\n";
  if (str) {
    length = strlen(str);
    data = new char[length + 1];
    strcpy(data, str);
  } else {
    data = new char[1];
    data[0] = '\0';
    length = 0;
  }
}

MyString::MyString(const MyString& other) {
  // cout << "[MyString copy ctor]\n";
  length = other.length;
  data = new char[length + 1];
  strcpy(data, other.data);
}

MyString::~MyString() {
  // cout << "[MyString dtor]\n";
  delete[] data;
}

char MyString::get(int i) const {
  if (i < 0 || i >= length) return '\0';
  return data[i];
}

void MyString::set(int i, char c) {
  if (i >= 0 && i < length) {
    data[i] = c;
  }
}

void MyString::set_new_string(const char* str) {
  delete[] data;
  if (str) {
    length = strlen(str);
    data = new char[length + 1];
    strcpy(data, str);
  } else {
    data = new char[1];
    data[0] = '\0';
    length = 0;
  }
}

void MyString::print() const {
  std::cout << data << "\n";
}

void MyString::read_line() {
  delete[] data;
  length = 0;
  int capacity = 10;
  data = new char[capacity];
  char ch;

  while (std::cin.get(ch) && ch != '\n') {
    if (length + 1 >= capacity) {
      capacity *= 2;
      char* newData = new char[capacity];
      strncpy(newData, data, length);
      delete[] data;
      data = newData;
    }
    data[length++] = ch;
  }
  data[length] = '\0';
}

void MyString::append(char c) {
  char* new_data = new char[length + 2];
  for (int i = 0; i < length; ++i) {
    new_data[i] = data[i];
  }
  new_data[length] = c;
  new_data[length + 1] = '\0';

  delete[] data;
  data = new_data;
  length++;
}

void MyString::append(const MyString& other) {
  if (other.length == 0) return;

  int new_length = length + other.length;
  char* new_data = new char[new_length + 1];

  strcpy(new_data, data);
  strcat(new_data, other.data);

  delete[] data;
  data = new_data;
  length = new_length;
}

int MyString::get_length() const {
  return length;
}

const char* MyString::get_data() const {
  return data;
}

MyString& MyString::operator=(const MyString& other) {
  if (this != &other) {
    delete[] data;
    length = other.length;
    data = new char[length + 1];
    strcpy(data, other.data);
  }
  return *this;
}

MyString& MyString::operator+=(const MyString& other) {
  append(other);
  return *this;
}

MyString& MyString::operator+=(const char* str) {
  append(str);
  return *this;
}

MyString operator+(const MyString& lhs, const MyString& rhs) {
  MyString result(lhs);
  result += rhs;
  return result;
}

MyString operator+(const MyString& lhs, const char* rhs) {
  MyString result(lhs);
  result += rhs;
  return result;
}

MyString operator+(const char* lhs, const MyString& rhs) {
  MyString result(lhs);
  result += rhs;
  return result;
}

// Move-конструктор
MyString::MyString(MyString&& other) noexcept {
  data = other.data;
  length = other.length;

  other.data = nullptr;
  other.length = 0;
}

// Move-оператор
MyString& MyString::operator=(MyString&& other) noexcept {
  if (this != &other) {
    delete[] data;

    data = other.data;
    length = other.length;

    other.data = nullptr;
    other.length = 0;
  }
  return *this;
}


bool MyString::operator==(const MyString& other) const {
  return strcmp(data, other.data) == 0;
}

bool MyString::operator!=(const MyString& other) const {
  return !(*this == other);
}

bool MyString::operator<(const MyString& other) const {
  return strcmp(data, other.data) < 0;
}

bool MyString::operator<=(const MyString& other) const {
  return strcmp(data, other.data) <= 0;
}

// с const char*
bool MyString::operator==(const char* str) const {
  return strcmp(data, str) == 0;
}

bool MyString::operator!=(const char* str) const {
  return !(*this == str);
}

bool MyString::operator<(const char* str) const {
  return strcmp(data, str) < 0;
}

bool MyString::operator<=(const char* str) const {
  return strcmp(data, str) <= 0;
}


bool operator==(const char* lhs, const MyString& rhs) {
  return rhs == lhs;
}

bool operator!=(const char* lhs, const MyString& rhs) {
  return rhs != lhs;
}

bool operator<(const char* lhs, const MyString& rhs) {
  return strcmp(lhs, rhs.get_data()) < 0;
}

bool operator<=(const char* lhs, const MyString& rhs) {
  return strcmp(lhs, rhs.get_data()) <= 0;
}

char& MyString::operator[](int index) {
  if (index < 0 || index >= length) {
    throw out_of_range("Index out of range in MyString::operator[]");
  }
  return data[index];
}

char MyString::operator[](int index) const {
  if (index < 0 || index >= length) {
    throw out_of_range("Index out of range in MyString::operator[] const");
  }
  return data[index];
}

ostream& operator<<(ostream& os, const MyString& str) {
  os << str.get_data();
  return os;
}

istream& operator>>(istream& is, MyString& str) {
  const int BUFFER_SIZE = 1024;
  char buffer[BUFFER_SIZE];

  is >> ws;
  int i = 0;
  char ch;

  while (is.get(ch) && !isspace(ch) && i < BUFFER_SIZE - 1) {
    buffer[i++] = ch;
  }

  buffer[i] = '\0';

  str.set_new_string(buffer);
  return is;
}
