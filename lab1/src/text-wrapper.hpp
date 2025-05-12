#include "my-string.hpp"

class TextWrapper {
public:
  TextWrapper(const MyString &input, int line_width);
  ~TextWrapper();

  void split_into_lines();
  void print_wrapped();

private:
  MyString input;
  int line_width;
  int* spaces;
  MyString* words;
  MyString* lines;
  int numWords;
  int numLines;
};