#include <ctype.h> /* tolower() */

typedef unsigned int hashval_t;

/************************************************************************/
/* hash functions */
/************************************************************************/

#define FNV_START() 1268436527
#define FNV_STEP(hash, c) (((hash) ^ tolower((c))) * 16777619)
#define FNV_FINISH(hash) ((hash) * 16777619)

/* FNV1A hash used in GSC  */
static hashval_t
t7_fnv1a(const char *str)
{
  hashval_t hash;

  if (str == NULL)
    return 0;

  hash = FNV_START();
  while (*str)
  {
    char c = *str++;
    hash = FNV_STEP(hash, c);
  }
  return FNV_FINISH(hash);
}

#define HS_START() 5381
#define HS_STEP(hash, c) (((hash) * 33) + tolower((c)))
#define HS_FINISH(hash) (hash)

/* internal hash used in GScr_HashString  */
static hashval_t
t7_hashstring(const char *str)
{
  hashval_t hash;

  if (str == NULL)
    return 0;

  hash = HS_START();
  while (*str)
  {
    char c = *str++;
    hash = HS_STEP(hash, c);
  }
  return HS_FINISH(hash);
}

/************************************************************************/
/* macros */
/************************************************************************/

/* parse options in a hash program  */
#define PARSE_OPTIONS             \
  do {                            \
    for (i = 1; i < argc; i++)    \
    {                             \
      char *arg = argv[i];        \
      if (arg[0] != '-')          \
        break;                    \
      if ( arg[1] == '-')         \
        break;                    \
      switch (arg[1])             \
      {                           \
        case 's':                 \
          usefnv = 0; break;      \
        default: break;           \
      }                           \
    }                             \
    hash_f = usefnv ?             \
      t7_fnv1a : t7_hashstring;   \
  } while (0)

/* make a string lowercase  */
#define make_lower(str)     \
  do {                      \
    char *p;                \
    for (p = str; *p; p++)  \
      *p = tolower(*p);     \
  } while (0)
