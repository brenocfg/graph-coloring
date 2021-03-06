#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "../../../common/common.h"

#ifndef M_METAHEURISTICS_H
#define M_METAHEURISTICS_H

uint32_t grasp_one_exchange_fixed_penalty(uint8_t *graph, uint16_t numv, uint32_t **answer, uint32_t c_n);
uint32_t one_exchange_fixed_penalty(uint8_t* graph, uint16_t numv, uint32_t **answer);
//uint32_t one_exchange_penalty(uint8_t* graph, uint16_t numv, uint32_t **answer);
uint32_t grasp(uint8_t* graph, uint16_t numv, uint32_t **answer);
uint32_t tabucol_search(uint8_t* graph, uint16_t numv, uint32_t **answer);

#endif /*M_METAHEURISTICS_H*/
