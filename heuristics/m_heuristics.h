#include <stdint.h> 

typedef struct vertex vertex_t;

struct vertex{
	uint32_t index;
	uint32_t degree;
};

uint32_t welsh_powell(int8_t* graph, int16_t numv);