
#pragma once
#include "my-string.hpp"

struct WorkerData {
  MyString name;
  int age;
  short experience;

  WorkerData() : name(), age(0), experience(0) {}
  WorkerData(const MyString& name_, int age_, short exp_) : name(name_), age(age_), experience(exp_) {}
};
