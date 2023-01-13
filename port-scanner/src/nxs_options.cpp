#include "nxs_options.h"


nxs_options * nxs_options::instance = nullptr;

option t_options[NUM_NXS_OPTIONS] = {
  {"-4",          NO_ARGS},
  {"-6",          NO_ARGS},
  {"-i",          HAS_ARGS},
  {"-p",          HAS_ARGS},
};


nxs_options * nxs_options::get_instance()
{
  if(!instance) instance = new nxs_options;

  return instance;
}


int nxs_options::parse(const int argc, const char ** argv)
{
  parse_options(argc, (char **)argv, (const option * const)&t_options, NUM_NXS_OPTIONS);

}