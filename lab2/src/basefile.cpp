#include "basefile.hpp"
#include <cstring>

#include <iostream>
using namespace std;

BaseFile::BaseFile() : file(nullptr) {
  cout << "[BaseFile ctor default]\n";
}

BaseFile::BaseFile(const char* path, const char* mode) {
  file = fopen(path, mode);
  cout << "[BaseFile ctor(path, mode)]\n";
  if (!is_open()) std::cerr << "Файл не открылся!\n";
}

BaseFile::BaseFile(FILE* existing_file) : file(existing_file) {
  cout << "[BaseFile ctor(FILE*)]\n";
}

BaseFile::~BaseFile() {
  if (file) fclose(file);
  cout << "[BaseFile dtor]\n";
}

bool BaseFile::is_open() const {
    return file != nullptr;
}

bool BaseFile::can_read() const {
    return is_open();
}

bool BaseFile::can_write() const {
    return is_open();
}

size_t BaseFile::write_raw(const void* buf, size_t n_bytes) {
    if (!can_write()) return 0;
    return fwrite(buf, 1, n_bytes, file);
}

size_t BaseFile::read_raw(void* buf, size_t max_bytes) {
    if (!can_read()) return 0;
    return fread(buf, 1, max_bytes, file);
}

long BaseFile::tell() const {
    if (!is_open()) return -1;
    return ftell(file);
}

bool BaseFile::seek(long offset) {
    if (!is_open()) return false;
    return fseek(file, offset, SEEK_SET) == 0;
}

size_t BaseFile::write(const void* buf, size_t n_bytes) {
    return write_raw(buf, n_bytes);
}

size_t BaseFile::read(void* buf, size_t max_bytes) {
    return read_raw(buf, max_bytes);
}
