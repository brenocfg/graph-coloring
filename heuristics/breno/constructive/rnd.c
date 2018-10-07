#include <stdio.h>
#include <stdlib.h>

#include "../common/common.h"

void randomize(uint32_t *array, uint32_t size) {
	if (size <= 1) {
		return;
	}

	int i;
	for (i = 0; i < size-1; i++) {
			int j = i + rand() / (RAND_MAX / (size - i) +1);
			int t = array[j];
			array[j] = array[i];
			array[i] = t;
	}
}

uint32_t rnd(int8_t* graph, int16_t num_ver) {
	uint32_t vers[num_ver];

	int i;
	for (i = 0; i < num_ver; i++) {
		vers[i] = i;
	}

	randomize(vers, num_ver);

	return 1;
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Usage: ./rnd <input_file>\n");
		return 1;
	}

	int16_t num_ver;
	int8_t *graph = read_input(argv[1], &num_ver);

	print_graph(graph, num_ver);
	uint32_t cost = rnd(graph, num_ver);

	uint32_t (*fun) (int8_t *g, int16_t v);
	fun = &rnd;

	double runtime = run(10, graph, num_ver, fun);
	free(graph);

	fprintf(stdout, "%d,%.64lf\n", cost, runtime);

	return 0;
}
