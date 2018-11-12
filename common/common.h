//----------------------Heuristics and Meta-heuristics-------------------------
//----------------Student: Breno Campos Ferreira Guimaraes---------------------

#ifndef COMMON_H
#define COMMON_H

#include <stdint.h> //portable types

/*Dumps graph to stderr, for debugging purposes*/
void print_graph(uint8_t *graph, uint16_t num_ver);

/*Reads TSP input instance and returns a complete graph of distances.*/
uint8_t *read_input(char *filename, uint16_t *num_ver);

/*Runs the given function @num_runs times and returns the average runtime
over all runs.*/
double run(uint8_t num_runs, uint8_t *graph, uint16_t num_ver,
							uint32_t(*fun) (uint8_t*, uint16_t, uint32_t**));

/*Check if its a feasible solution*/
int check_solution(uint8_t* graph, uint16_t numv, uint32_t *colors);

#endif /*COMMON_H*/
