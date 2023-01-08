#pragma once

#include <stdio.h>
#include <vector>
#include <inttypes.h>

class nxs_options{
  // singleton stuff
  nxs_options(){}
  static nxs_options * instance;

  std::vector<unsigned int> target_ports;
  std::vector<uint32_t> targetIpv4Addrs;


public:
  // singleton stuff
  void operator=(const nxs_options &) = delete;
  nxs_options(const nxs_options &) = delete;
  static nxs_options * get_instance();

  int parse_options(const int argc, const char ** argv);



};


