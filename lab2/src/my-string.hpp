#pragma once
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
        int get_length() const;
        const char* get_data() const;
    
        MyString& operator=(const MyString& other);
    };
    