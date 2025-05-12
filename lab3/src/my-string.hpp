#pragma once
#include <iostream>

class MyString {
  private:
    char* data;
    int length;

  public:
    MyString();
    MyString(const char* str);
    MyString(const MyString& other);
    ~MyString();

    char get(int i) const;
    void set(int i, char c);
    void set_new_string(const char* str);
    void print() const;
    void read_line();
    void append(char c);
    void append(const MyString& other);
    int get_length() const;
    const char* get_data() const;

    MyString& operator=(const MyString& other);

    MyString& operator+=(const MyString& other);
    MyString& operator+=(const char* str);

    friend MyString operator+(const MyString& lhs, const MyString& rhs);
    friend MyString operator+(const MyString& lhs, const char* rhs);
    friend MyString operator+(const char* lhs, const MyString& rhs);

    //Move
    MyString(MyString&& other) noexcept;
    MyString& operator=(MyString&& other) noexcept;

    //Сравнения
    bool operator==(const MyString& other) const;
    bool operator!=(const MyString& other) const;
    bool operator<(const MyString& other) const;
    bool operator<=(const MyString& other) const;

    bool operator==(const char* str) const;
    bool operator!=(const char* str) const;
    bool operator<(const char* str) const;
    bool operator<=(const char* str) const;

    friend bool operator==(const char* lhs, const MyString& rhs);
    friend bool operator!=(const char* lhs, const MyString& rhs);
    friend bool operator<(const char* lhs, const MyString& rhs);
    friend bool operator<=(const char* lhs, const MyString& rhs);

    //Индексирование
    char& operator[](int index);
    char operator[](int index) const;

    
  };
  
std::ostream& operator<<(std::ostream& os, const MyString& str);
std::istream& operator>>(std::istream& is, MyString& str);