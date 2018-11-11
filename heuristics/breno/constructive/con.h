#include <stdint.h>

#ifndef RND_H
#define RND_H

struct vertex;

/*Runs the Random Ordered Sequential greedy coloring algorithm on the given
graph, storing the solution in @colors. Returns number of colors used.*/
uint32_t rnd(uint8_t *graph, uint16_t num_ver, uint32_t **colors);

/*Runs the Smallest Neighborhood Tiebreaking version of the Largest Degree
First heuristic on the given graph, storing the solution in @colors.
Returns number of colors used.*/
uint32_t snt(uint8_t *graph, uint16_t num_ver, uint32_t **colors);

#endif /*RND_H*/
