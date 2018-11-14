#include <stdint.h>

#ifndef META_H
#define META_H

struct vertex;

uint32_t ils(uint8_t *graph, uint16_t numv, uint32_t **answer);

uint32_t sa(uint8_t *graph, uint16_t numv, uint32_t **answer);

#endif /*META_H*/
