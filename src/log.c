
#include <stdio.h>
#include <stdint.h>

#include "hash.h"

char g_hashtable_name[] = "hashes.csv";

int main(int argc, const char **argv)
{
  int i;
  FILE *f;

  if ( !(f = fopen(g_hashtable_name, "a")) ) {
    fprintf(stderr, "Could not open file `%s` for logging.\n",
      g_hashtable_name);
    return 1;
  }

  for (i = 1; i < argc; i++) {
    uint32_t hash = hash_t7(argv[i]);
    fprintf(f, "%x,%s\n", hash, argv[i]);
  }

  fclose(f);
  return 0;
}
