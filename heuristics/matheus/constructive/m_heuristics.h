#include <stdint.h>

#ifndef M_HEURISTICS_H
#define M_HEURISTICS_H

typedef struct vertex vertex_t;

struct vertex{
	uint32_t index;
	uint32_t degree;
	uint32_t region;
};

uint32_t welsh_powell(uint8_t* graph, uint16_t numv, uint32_t **answer);
uint32_t welsh_powell_brtiebreak(uint8_t* graph, uint16_t numv, uint32_t **answer);

#endif /*M_HEURISTICS_H*/
