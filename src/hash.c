
#include <stdio.h>
#include <stdint.h>

#include "hash.h"

int main(int argc, const char **argv)
{
  int i;
  for (i = 1; i < argc; i++) {
    uint32_t hash = hash_t7(argv[i]);
    printf("%s: %x\n", argv[i], hash);
  }

  return 0;
}
