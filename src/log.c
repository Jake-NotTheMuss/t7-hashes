#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "hash.h"

#define FNVFILENAME     "hashes.csv"
#define STRINGFILENAME  "hashes_strings.csv"

int
main(int argc, char **argv)
{
  int i;
  int usefnv = 1;
  hashval_t (*hash_f)(const char *);
  FILE *f;

  PARSE_OPTIONS;

  {
    char *filename = usefnv ?
          FNVFILENAME : STRINGFILENAME;
    if (!(f = fopen(filename, "a")))
    {
      fprintf(stderr,
       "cannot not open file `%s'\n",
       filename);
      return EXIT_FAILURE;
    }
  }

  for (; i < argc; i++) {
    make_lower(argv[i]);
    hashval_t hash = (*hash_f)(argv[i]);
    fprintf(f, "%x,%s\n", hash, argv[i]);
  }

  fclose(f);
  return EXIT_SUCCESS;
}
