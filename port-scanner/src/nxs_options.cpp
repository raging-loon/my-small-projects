#include "nxs_options.h"


nxs_options * nxs_options::instance = nullptr;


nxs_options * nxs_options::get_instance()
{
  if(!instance) instance = new nxs_options;

  return instance;
}