//----------------------Heuristics and Meta-heuristics-------------------------
//----------------Student: Breno Campos Ferreira Guimaraes---------------------

#include <stdint.h> //portable types

/*Dumps graph to stderr, for debugging purposes*/
void print_graph(int8_t *graph, int16_t num_ver);

/*Reads TSP input instance and returns a complete graph of distances.*/
int8_t *read_input(char *filename, int16_t *num_ver);

/*Runs the given function @num_runs times and returns the average runtime
over all runs.*/
double run(int8_t num_runs, int8_t *graph, int16_t num_ver,
										uint32_t(*fun) (int8_t*, int16_t));
