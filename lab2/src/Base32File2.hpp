#pragma once
#include "IFile.hpp"
#include "my-string.hpp"

class Base32File2 : public IFile {
private:
  IFile* inner;
  MyString encode_table;

public:
  Base32File2(IFile* file);
  ~Base32File2();

  bool can_read() const override;
  bool can_write() const override;
  size_t write(const void* buf, size_t n_bytes) override;
  size_t read(void* buf, size_t max_bytes) override;

private:
  int encode32(const MyString& raw_data, MyString& dst);
};
