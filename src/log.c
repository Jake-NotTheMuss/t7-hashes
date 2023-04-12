#include <stdio.h>
#include <stdlib.h>

#define PROG_LOG_C

#include "hash.h"

int
main(int argc, char **argv)
{
  COMMON_DECLS;
  FILE *f;
  const char *filename;
  PARSE_OPTIONS;

  if (usefnv)
    filename = "hashes.csv";
  else if (hashuserdata)
    filename = "hashes_ud.csv";
  else
    filename = "hashes_strings.csv";

  if (!(f = fopen(filename, "a")))
  {
    fprintf(stderr, "cannot not open file `%s'\n", filename);
    return EXIT_FAILURE;
  }

  for (; i < argc; i++) {
    PRINT_HASH(f, argv[i], (*hash_f)(argv[i]));
  }

  fclose(f);
  return EXIT_SUCCESS;
}
