
#include <stdint.h>

static inline uint32_t fnv1a(const char* key) {

	const char* data = key;
	uint32_t hash = 0x4B9ACE2F;
	while(*data)
	{
		hash ^= *data;
		hash *= 0x1000193;
		data++;
	}
	hash *= 0x1000193;
	return hash;
}

#define hash_t7 fnv1a
