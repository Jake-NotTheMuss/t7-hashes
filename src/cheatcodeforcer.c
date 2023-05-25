/*
** cheatcodeforcer.c
** Black Ops 3 campaign cheat-code brute forcer
*/

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>

#if INT_MAX-20 < 32760
#define HASH32 unsigned long
#define HASH32_FMT "%lx"
#else
#define HASH32 unsigned int
#define HASH32_FMT "%x"
#endif

#if ULONG_MAX > 0xFFFFFFFFUL && ULONG_MAX == 0xFFFFFFFFFFFFFFFFUL
#define HASH64 unsigned long
#define HASH64_FMT "%lx"
#define H64(x) x##lu
#define STR2H64(s,p,n) strtoul(s,p,n)
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#define HASH64 unsigned long long
#define HASH64_FMT "%llx"
#define H64(x) x##llu
#define STR2H64(s,p,n) strtoull(s,p,n)
#else
#error no 64-bit type found
#endif

#include "xxhash.h"

static HASH64 hashud(char *s, size_t len)
{
  return (HASH64)XXH64(s, len, H64(0x6CDFB2E4013EB3F3));
}


#define MAXBUFF 10

static char buff[MAXBUFF+1];
static HASH64 hashtofind;

void step(char *const pos, char *const lim)
{
  size_t len = (size_t)(lim-buff);
  int c;
  for (c = 'A'; c <= 'Z'; c++) {
    HASH64 result;
    *pos = c;
    if (pos+1 != lim) {
      step(pos+1,lim);
      continue;
    }
    result = hashud(buff, len);
    if (result == hashtofind) {
      printf("%s --> " HASH64_FMT "\n", buff, result);
      exit(0);
    }
  }
}


/* MANIFEST */
/* DREAMLAND - removed */
/* JACKWALL - removed */
/* WALKER - 0x2d05129b69c7715a */
/* CAMPFIRE - 0x35e1ceb04f5016ed */
/* GOTITALL - 0xc835383d1a90c16e */
/* TELLMEALL - 0xe242980a0f0968a3 */

int main(int argc, char **argv)
{
  int i;
  char *lim;
  char *endptr;
  if (argc < 1)
    return 1;
  if (argc < 2) {
    printf("usage: %s [HASH in base 16]\n", argv[0]);
    return 1;
  }
  hashtofind = (HASH64)STR2H64(argv[1], &endptr, 16);
  if (*endptr != '\0')
    return 1;
  for (i = 0; i < MAXBUFF; i++) {
    lim = &buff[i+1];
    step(&buff[0],lim);
    printf("step %d complete\n", i+1);
  }

  return 0;
}


