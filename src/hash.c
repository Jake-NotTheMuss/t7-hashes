#include <stdio.h>
#include <stdlib.h>

#define PROG_HASH_C

#include "hash.h"

int
main(int argc, char **argv)
{
  COMMON_DECLS;
  PARSE_OPTIONS;
  for (; i < argc; i++) {
    PRINT_HASH(stdout, argv[i], (*hash_f)(argv[i]));
  }
  return EXIT_SUCCESS;
}
