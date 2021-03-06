#include <stdlib.h>
#include <stdio.h>

#include "common/common.h"
#include "heuristics/matheus/constructive/m_heuristics.h"
#include "heuristics/matheus/metaheuristics/m_metaheuristics.h"
#include "heuristics/breno/constructive/con.h"
#include "heuristics/breno/metaheuristics/meta.h"

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

	srand(32);

	/*cost = rnd(graph, numv, &ans);
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
	fprintf(stdout, "%d,", cost);*/

	cost = sa(graph, numv, &ans);
	avg = run(atoi(argv[2]), graph, numv, sa);
	fprintf(stdout, "%d\n", cost);

	/*cost = grasp(graph, numv, &ans);
	avg = run(atoi(argv[2]), graph, numv, grasp);
	fprintf(stdout, "%d,", cost);

	cost = ils(graph, numv, &ans);
	avg = run(atoi(argv[2]), graph, numv, ils);
	fprintf(stdout, "%d\n", cost);
	
	cost = tabucol_search(graph, numv, &ans);
	avg = run(atoi(argv[2]), graph, numv, tabucol_search);
	fprintf(stdout, "%d\n", cost);*/

	return 0;
}
