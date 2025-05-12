#include "my-string.hpp"
#include <cstring>
#include <iostream>


MyString::MyString() : data(nullptr), length(0) {
    data = new char[1];
    data[0] = '\0';
}

MyString::MyString(const char* str) {
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
    length = other.length;
    data = new char[length + 1];
    strcpy(data, other.data);
}

MyString::~MyString() {
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

MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {
        delete[] data;
        length = other.length;
        data = new char[length + 1];
        strcpy(data, other.data);
    }
    return *this;
}