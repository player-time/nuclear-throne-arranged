#include <stdio.h>
#include <stdlib.h>

#include <stdint.h>

#define da_append(vec, val)\
do{\
	if (vec.count >= vec.capacity) {\
			vec.capacity *= 2; \
			vec.array_positions = (int *)realloc(vec.array_positions, vec.capacity * sizeof(*vec.array_positions)); \
	}\
	vec.array_positions[vec.count++] = val; \
} while(0)

#define da_clear(vec)\
do{\
	vec.count = 0;\
} while(0)

struct vector_small {
	int *array_positions;
	unsigned short count;
	unsigned short capacity = 1;
};