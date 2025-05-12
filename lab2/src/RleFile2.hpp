#pragma once
#include "IFile.hpp"
#include "my-string.hpp"

class RleFile2 : public IFile {
private:
  IFile* inner;

public:
  RleFile2(IFile* file);
  ~RleFile2();

  bool can_read() const override;
  bool can_write() const override;
  size_t write(const void* buf, size_t n_bytes) override;
  size_t read(void* buf, size_t max_bytes) override;

private:
  MyString encode(const MyString& input);
};
