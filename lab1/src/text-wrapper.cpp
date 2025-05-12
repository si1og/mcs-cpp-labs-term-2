#include "text-wrapper.hpp"
#include <iostream>

TextWrapper::TextWrapper(const MyString &input, int line_width) 
    : input(input), line_width(line_width), spaces(nullptr), words(nullptr), lines(nullptr), numWords(0), numLines(0) {}

TextWrapper::~TextWrapper() {
    delete[] spaces;
    delete[] words;
    delete[] lines;
}

void TextWrapper::split_into_lines() {
  const int SPACE = 32;

  int input_length = 0;
  while (input.get(input_length) != '\0') input_length++;

  MyString* tempWords = new MyString[input_length];
  int* tempSpaces = new int[input_length + 1]();
  int wordCount = 0;
  MyString currentWord;

  for (int i = 0; i < input_length; ++i) {
      char c = input.get(i);
      if (c == SPACE) {
          if (currentWord.get(0) != '\0') {
              tempWords[wordCount++] = currentWord;
              currentWord.set_new_string("");
          }
          tempSpaces[wordCount]++;
      } else {
          int len = 0;
          while (currentWord.get(len) != '\0') len++;
          char* newStr = new char[len + 2];
          for (int j = 0; j < len; ++j) newStr[j] = currentWord.get(j);
          newStr[len] = c;
          newStr[len + 1] = '\0';
          currentWord.set_new_string(newStr);
          delete[] newStr;
      }
  }
  if (currentWord.get(0) != '\0') tempWords[wordCount++] = currentWord;
  
  delete[] words;
  delete[] spaces;
  words = new MyString[wordCount];
  spaces = new int[wordCount + 1];
  for (int i = 0; i < wordCount; ++i) words[i] = tempWords[i];
  for (int i = 0; i <= wordCount; ++i) spaces[i] = tempSpaces[i];
  numWords = wordCount;
  delete[] tempWords;
  delete[] tempSpaces;

  delete[] lines;
  lines = new MyString[wordCount * 2];
  numLines = 0;
  MyString currentLine;
  int currentLength = 0;

  for (int i = 0; i < numWords; ++i) {
    int spaceCount = (i == 0) ? 0 : spaces[i];
    int wordLength = 0;
    while (words[i].get(wordLength) != '\0') wordLength++;

    if (currentLength + spaceCount + wordLength > line_width) {
      lines[numLines++] = currentLine;
      currentLine.set_new_string("");
      currentLength = 0;
      spaceCount = 0;
    }

    if (spaceCount > 0) {
      char* spacesStr = new char[spaceCount + 1];
      for (int j = 0; j < spaceCount; ++j) spacesStr[j] = ' ';
      spacesStr[spaceCount] = '\0';
      MyString spaceMS(spacesStr);
      delete[] spacesStr;

      MyString newLine;
      int newLen = currentLength + spaceCount;
      char* temp = new char[newLen + 1];
      for (int j = 0; j < currentLength; ++j) temp[j] = currentLine.get(j);
      for (int j = 0; j < spaceCount; ++j) temp[currentLength + j] = ' ';
      temp[newLen] = '\0';
      newLine.set_new_string(temp);
      delete[] temp;
      currentLine = newLine;
      currentLength = newLen;
    }

    char* newStr = new char[currentLength + wordLength + 1];
    for (int j = 0; j < currentLength; ++j) newStr[j] = currentLine.get(j);
    for (int j = 0; j < wordLength; ++j) newStr[currentLength + j] = words[i].get(j);
    newStr[currentLength + wordLength] = '\0';
    currentLine.set_new_string(newStr);
    delete[] newStr;
    currentLength += wordLength;
  }

  if (currentLine.get(0) != '\0') lines[numLines++] = currentLine;
}

void TextWrapper::print_wrapped() {
    split_into_lines();

    std::cout << ' ';
    for (int i = 0; i < line_width + 2; ++i) std::cout << '-';
    std::cout << std::endl;

    for (int i = 0; i < numLines; ++i) {
        if (i == 0 && numLines != 1) std::cout << "/ ";
        else if (i > 0 && i < numLines - 1 || numLines == 1) std::cout << "| ";
        else std::cout << "\\ ";

        for (int j = 0; j < line_width; ++j) {
            char c = lines[i].get(j);
            std::cout << (c != '\0' ? c : ' ');
        }

        if (i == 0 && numLines != 1) std::cout << " \\" << std::endl;
        else if (i > 0 && i < numLines - 1 || numLines == 1) std::cout << " |" << std::endl;
        else std::cout << " /" << std::endl;
    }

    std::cout << ' ';
    for (int i = 0; i < line_width + 2; ++i) std::cout << '-';
    std::cout << std::endl;

    std::cout << "     \\" << std::endl;
    std::cout << "      \\" << std::endl;
    std::cout << "        /\\_/\\  (" << std::endl;
    std::cout << "       ( ^.^ ) _)" << std::endl;
    std::cout << "         \"/  (" << std::endl;
    std::cout << "       ( | | )" << std::endl;
    std::cout << "      (__d b__)" << std::endl;
}