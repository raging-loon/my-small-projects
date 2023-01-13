#ifndef LIBOPTIONS_H
#define LIBOPTIONS_H
#ifdef __cplusplus
extern "C"{
#endif

#include <stdbool.h>


#define NO_ARGS false
#define HAS_ARGS true


typedef struct option{
  char * option_name;
  bool has_args;
} option;




extern int parse_options(int argc, char ** argv, 
                          const option * const option_list, const int n_options);

#ifdef __cplusplus
}
#endif

#endif /* LIBOPTIONS_H */