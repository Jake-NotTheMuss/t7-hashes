#include <stdio.h>
#include <stdlib.h>

#include "hash.h"

int
main(int argc, char **argv)
{
  int i;
  int usefnv = 1;
  hashval_t (*hash_f)(const char *);

  PARSE_OPTIONS;

  for (; i < argc; i++) {
    hashval_t hash = (*hash_f)(argv[i]);
    printf("%s:%x\n", argv[i], hash);
  }

  return EXIT_SUCCESS;
}
