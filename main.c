#include <stdlib.h>
#include <stdio.h>

#include "common/common.h"
#include "heuristics/matheus/constructive/m_heuristics.h"
#include "heuristics/breno/constructive/con.h"

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
	uint32_t cost, *ans;
	double avg;

	cost = rnd(graph, numv, &ans);
	avg = run(atoi(argv[2]), graph, numv, rnd);
	fprintf(stdout, "%d,", cost);

	cost = welsh_powell(graph, numv, &ans);
	avg = run(atoi(argv[2]), graph, numv, welsh_powell);
	fprintf(stdout, "%d,", cost);

	cost = snt(graph, numv, &ans);
	avg = run(atoi(argv[2]), graph, numv, snt);
	fprintf(stdout, "%d,", cost);

	cost = welsh_powell_brtiebreak(graph, numv, &ans);
	avg = run(atoi(argv[2]), graph, numv, welsh_powell_brtiebreak);
	fprintf(stdout, "%d\n", cost);

	return 0;
}
