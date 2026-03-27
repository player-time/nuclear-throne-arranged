#include <stdio.h>
#include <stdlib.h>

#include <stdint.h>

#define da_append(vec, val)\
do{\
	if (vec.count >= vec.capacity) {\
			vec.capacity++; \
			vec.array_positions = realloc(vec.array_positions, vec.capacity * sizeof(*vec.array_positions)); \
			vec.array_positions[vec.count++] = val; \
	}\
} while(0)

#define da_clear(vec)\
do{\
	for(int i = 0; i < vec.count; i++){\
		vec.array_positions[i] = 65535;\
	}\
} while(0)

struct vector_small {
	std::uint16_t *array_positions;
	unsigned short count;
	unsigned short capacity = 1;
};