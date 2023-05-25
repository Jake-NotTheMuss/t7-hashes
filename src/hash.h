/* common header for hash programs */

/* check which type can fit a 32-bit hash */
#include <limits.h>
#include <string.h>
#if INT_MAX-20 < 32760
# define HASHVAL32_TYPE unsigned long
# define HASHVAL32_FMT "%x"
#else
# define HASHVAL32_TYPE unsigned int
# define HASHVAL32_FMT "%x"
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
#ifdef _WIN32
#define HASH64 unsigned __int64
#define HASH64_FMT "%X64"
#define H64(x) x
#else
#error no 64-bit type found
#endif
#endif

typedef HASHVAL32_TYPE hashval_t;
typedef HASHVAL32_TYPE hashval32_t;
typedef HASH64 hashval64_t;

#if 'A' == 65 && '0' == 48
/* ASCII case: can use its own tables; faster and fixed */
static const unsigned char _sch_tolower[256] =
{
   0,  1,  2,  3,   4,  5,  6,  7,   8,  9, 10, 11,  12, 13, 14, 15,
  16, 17, 18, 19,  20, 21, 22, 23,  24, 25, 26, 27,  28, 29, 30, 31,
  32, 33, 34, 35,  36, 37, 38, 39,  40, 41, 42, 43,  44, 45, 46, 47,
  48, 49, 50, 51,  52, 53, 54, 55,  56, 57, 58, 59,  60, 61, 62, 63,
  64,

  'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
  'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',

  91, 92, 93, 94, 95, 96,

  'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
  'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',

 123,124,125,126,127,

 128,129,130,131, 132,133,134,135, 136,137,138,139, 140,141,142,143,
 144,145,146,147, 148,149,150,151, 152,153,154,155, 156,157,158,159,
 160,161,162,163, 164,165,166,167, 168,169,170,171, 172,173,174,175,
 176,177,178,179, 180,181,182,183, 184,185,186,187, 188,189,190,191,

 192,193,194,195, 196,197,198,199, 200,201,202,203, 204,205,206,207,
 208,209,210,211, 212,213,214,215, 216,217,218,219, 220,221,222,223,
 224,225,226,227, 228,229,230,231, 232,233,234,235, 236,237,238,239,
 240,241,242,243, 244,245,246,247, 248,249,250,251, 252,253,254,255,
};
static const unsigned char _sch_toupper[256] =
{
   0,  1,  2,  3,   4,  5,  6,  7,   8,  9, 10, 11,  12, 13, 14, 15,
  16, 17, 18, 19,  20, 21, 22, 23,  24, 25, 26, 27,  28, 29, 30, 31,
  32, 33, 34, 35,  36, 37, 38, 39,  40, 41, 42, 43,  44, 45, 46, 47,
  48, 49, 50, 51,  52, 53, 54, 55,  56, 57, 58, 59,  60, 61, 62, 63,
  64,

  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
  'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',

  91, 92, 93, 94, 95, 96,

  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
  'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',

 123,124,125,126,127,

 128,129,130,131, 132,133,134,135, 136,137,138,139, 140,141,142,143,
 144,145,146,147, 148,149,150,151, 152,153,154,155, 156,157,158,159,
 160,161,162,163, 164,165,166,167, 168,169,170,171, 172,173,174,175,
 176,177,178,179, 180,181,182,183, 184,185,186,187, 188,189,190,191,

 192,193,194,195, 196,197,198,199, 200,201,202,203, 204,205,206,207,
 208,209,210,211, 212,213,214,215, 216,217,218,219, 220,221,222,223,
 224,225,226,227, 228,229,230,231, 232,233,234,235, 236,237,238,239,
 240,241,242,243, 244,245,246,247, 248,249,250,251, 252,253,254,255,
};
#define TOLOWER(c) _sch_tolower[(c)]
#define TOUPPER(c) _sch_toupper[(c)]
#else
/* must use standard C ctype */
#include <ctype.h>
#define TOLOWER(c) tolower(c)
#define TOUPPER(c) toupper(c)
#endif

/************************************************************************/
/* hash functions */
/************************************************************************/

#define FNV_START() 1268436527
#define FNV_STEP(hash, c) (((hash) ^ (c)) * 16777619)
#define FNV_FINISH(hash) ((hash) * 16777619)

/* FNV1A hash used in GSC  */
static hashval64_t
t7_fnv1a(const char *str)
{
  char c;
  hashval_t hash;
  if (str == NULL) return 0;
  /* compute hash */
  hash = FNV_START();
  while ((c = *str))
  {
    c = (char)TOLOWER(c);
#ifdef PROG_LOG_C
    *(char *)str = c;
#endif /* PROG_LOG_C */
    hash = FNV_STEP(hash, c);
    str++;
  }
  return (hashval64_t)FNV_FINISH(hash);
}

#define HS_START() 5381
#define HS_STEP(hash, c) (((hash) * 33) + (c))
#define HS_FINISH(hash) (hash)

/* internal hash used in GScr_HashString  */
static hashval64_t
t7_hashstring_i(const char *str)
{
  char c;
  hashval_t hash;
  if (str == NULL) return 0;
  /* compute hash */
  hash = HS_START();
  while ((c = *str))
  {
    c = (char)TOLOWER(c);
#ifdef PROG_LOG_C
    *(char *)str = c;
#endif /* PROG_LOG_C */
    hash = HS_STEP(hash, c);
    str++;
  }
  return (hashval64_t)HS_FINISH(hash);
}

static hashval64_t
t7_hashstring(const char *str)
{
  char c;
  hashval_t hash;
  if (str == NULL) return 0;
  /* compute hash */
  hash = HS_START();
  while ((c = *str++))
    hash = HS_STEP(hash, c);
  return (hashval64_t)HS_FINISH(hash);
}


void make_upper(char *str)
{
  char *p = str;
  while (*p) {
    *p = TOUPPER(*p);
    p++;
  }
}

#include "xxhash.h"

static hashval64_t t7_hashuserdata(const char *str)
{
  size_t len = strlen(str);
  make_upper((char *)str);
  return (hashval64_t)XXH64(str, len, H64(0x6CDFB2E4013EB3F3));
}

/************************************************************************/
/* macros */
/************************************************************************/
#ifdef PROG_LOG_C
# define HASH_FMT_HEX HASH64_FMT ",%s\n"
# define PRINT_HASH(f,str,hash) fprintf(f, print_fmt, hash, str)
#else
# define HASH_FMT_HEX "%s:" HASH64_FMT "\n"
# define PRINT_HASH(f,str,hash) fprintf(f, print_fmt, str, hash)
#endif /* PROG_LOG_C */


#define COMMON_DECLS   int i; \
  int usefnv = 1; \
  int usecase = 0; \
  int hashuserdata = 0; \
  const char *print_fmt = HASH_FMT_HEX; \
  hashval64_t (*hash_f)(const char *)

/* don't use case-sensitive hashing when logging */
#ifdef PROG_LOG_C
# define CASE_C case 'c': break
#else /* !PROG_LOG_C */
# define CASE_C case 'c': usecase = 1; break
#endif /* PROG_LOG_C */


/* parse options in a hash program  */
#define PARSE_OPTIONS             \
  do {                            \
    for (i = 1; i < argc; i++)    \
    {                             \
      char *arg = argv[i];        \
      if (arg[0] != '-')          \
        break;                    \
      if ( arg[1] == '-')         \
        { i++; break; }           \
      while (*++arg)              \
      {                           \
        switch (*arg)             \
        {                         \
          case 's':               \
            usefnv = 0; break;    \
          case 'u':               \
          case 'x':               \
            usefnv = 0;           \
            hashuserdata = 1;     \
            break;                \
          CASE_C;                 \
          default: break;         \
        }                         \
      }                           \
    }                             \
    hash_f = usefnv ?             \
      t7_fnv1a :                  \
        (hashuserdata ?           \
         t7_hashuserdata :        \
      (usecase ? t7_hashstring  : \
       t7_hashstring_i));         \
  } while (0)
