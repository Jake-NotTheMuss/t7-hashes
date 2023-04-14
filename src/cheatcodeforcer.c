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
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#define HASH64 unsigned long long
#define HASH64_FMT "%llx"
#define H64(x) x##llu
#else
#error no 64-bit type found
#endif

typedef HASH32 hashval32_t;
typedef HASH64 hashval64_t;

hashval64_t hash_userdata(const char *str, size_t len, hashval64_t offset)
{
  const hashval64_t *p = (const hashval64_t *)str;
  const char *pc;
  const hashval64_t *limit = (const hashval64_t *)(str + len);
  hashval64_t hash = (hashval64_t)len;
  hashval64_t v8 = offset + H64(0x27D4EB2F165667C5);
  hash = v8 + hash;
  while (p + 1 <= limit) {
    hashval64_t c = *p;
    hash = hash ^ (c * H64(0x93EA75A780000000) | (c * H64(0xC2B2AE3D27D4EB4F)) >> 33) *
    H64(0x9E3779B185EBCA87);
    hash = (hash << 27 | hash >> 37) * H64(0x9E3779B185EBCA87) + H64(0x85EBCA77C2B2AE63);
    p++;
  }
  if (((hashval64_t *)((hashval32_t *)p + 1)) <= limit) {
    hashval64_t c = ((hashval64_t)(*(hashval32_t *)p));
    hash = hash ^ c * H64(0x9E3779B185EBCA87);
    hash = (hash << 23 | hash >> 41) * H64(0xC2B2AE3D27D4EB4F) + H64(0x165667B19E3779F9);
    p = (hashval64_t *)((hashval32_t *)p + 1);
  }
  for (; p < limit; p = (hashval64_t *)((char *)p + 1)) {
    hashval64_t c = ((hashval64_t)(*(char *)p));
    hash = hash ^ c * H64(0x27D4EB2F165667C5);
    hash = (hash << 11 | hash >> 53) * H64(0x9E3779B185EBCA87);
  }
  hash = (hash >> 33 ^ hash) * H64(0xC2B2AE3D27D4EB4F);
  hash = (hash >> 29 ^ hash) * H64(0x165667B19E3779F9);
  return hash >> 32 ^ hash;
}

static hashval64_t hashud(char *s, size_t len)
{
  return hash_userdata(s, len, H64(0x6CDFB2E4013EB3F3));
}


#define MAXBUFF 10

static char buff[MAXBUFF+1];

void step(char *pos, char *lim)
{
  size_t len = (size_t)(lim-buff);
  int c;
  if (pos == lim) {
    *pos = '\0';
    return;
  }
  for (c = 'A'; c <= 'Z'; c++) {
    hashval64_t result;
    *pos = c;
    step(pos+1,lim);
    result = hashud(buff, len);
    if (result == H64(0xe242980a0f0968a3)) {
      printf("%s --> " HASH64_FMT "\n", buff, result);
      exit(0);
    }
    /*puts(buff);*/
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
  for (i = 0; i < MAXBUFF; i++) {
    lim = &buff[i+1];
    step(&buff[0],lim);
    printf("step %d complete\n", i+1);
  }

  (void)argc; (void)argv;
  return 0;
}


