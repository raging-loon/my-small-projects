#pragma once

#include <stdio.h>

class nxs_options{

  nxs_options(){}

  static nxs_options * instance;
public:
  nxs_options(const nxs_options &) = delete;

  void print() { printf("singleton"); }
  static nxs_options * get_instance();
};


