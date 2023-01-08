#include "nxs_options.h"


nxs_options * nxs_options::instance = nullptr;


nxs_options * nxs_options::get_instance()
{
  if(!instance) instance = new nxs_options;

  return instance;
}


int nxs_options::parse_options(const int argc, const char ** argv)
{
  for(int i = 0; i < argc; i++) printf("%s\n",argv[i]);
}