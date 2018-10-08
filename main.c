#include <stdlib.h>
#include <stdio.h>

#include "common/common.h"
#include "heuristics/matheus/constructive/m_heuristics.h"
#include "heuristics/breno/constructive/rnd.h"

int main(int argc, char* argv[]){
	uint16_t numv;

	if (argc < 3) {
		fprintf(stderr, "Usage: ./tp <input_file> <num_runs>\n");
		return 1;
	}

	uint8_t *graph = read_input(argv[1], &numv);
	if (graph == NULL) {
		fprintf(stderr, "Fatal error: no input file.\n");
		return 1;
	}

	/*welsh powell algorithm (greedy largest degree first)*/
	run(atoi(argv[2]), graph, numv, welsh_powell);

	/*random sequential ordering algorithm (greedy random order)*/
	run(atoi(argv[2]), graph, numv, rnd);

	return 0;
}
