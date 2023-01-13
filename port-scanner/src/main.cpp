#include <stdio.h>

#include <nxs_options.h>


int main(int argc, char ** argv)
{

  nxs_options::get_instance()->parse((const int)argc, (const char **)argv);



}