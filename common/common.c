#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "common.h"

void print_graph (int8_t *graph, int16_t num_ver) {
	int16_t i, j;

	for (i = 0; i < num_ver; i++) {
		for (j = 0; j < num_ver; j++) {
			fprintf(stderr, "%d\t", graph[i * num_ver + j]);
		}
		fprintf(stderr, "\n");
	}
}


int check_solution(int8_t* graph, int16_t numv, uint32_t *colors){
	uint32_t i,j;
	for (i = 0; i < numv; i++) 
		for (j = 0; j < numv; j++) 
			if(graph[i*numv + j] && colors[i]==colors[j])
				return 1;

	return 0;
}

int8_t *read_input(char *filename, int16_t *num_ver) {
	FILE *input;

	input = fopen(filename, "r");
	if (input == NULL) {
		fprintf(stderr, "Error reading input file!\n");
		return 0;
	}

	int type, numv, nume;
	fscanf(input, "%d %d\n", &numv, &nume);
	*num_ver = numv;

	int8_t *graph = (int8_t*) malloc(numv*numv*sizeof(int8_t));
	memset(graph, 0, numv*numv*sizeof(int8_t));
	uint32_t i;
	for (i = 0; i < nume; i++) {
		int32_t v1, v2;
		fscanf(input, "%d %d\n", &v1, &v2);
		graph[(v1-1)*numv + (v2-1)] = 1;
		graph[(v2-1)*numv + (v1-1)] = 1;
	}

	fclose(input);

	return graph;
}

double run(int8_t num_runs, int8_t *graph, int16_t num_cities,
										uint32_t(*fun) (int8_t*, int16_t, uint32_t**)) {
	clock_t begin, end;
	double total = 0.0;
	uint32_t *colors;
	uint8_t i;

	for (i = 0; i < num_runs; i++) {
		fprintf(stderr, "----- RUN #%d -----\n", i+1);
		begin = clock();
		fprintf(stderr, "Function returned %d\n", fun(graph, num_cities,&colors));
		end = clock();
		if(check_solution(graph,num_cities,colors)){
			fprintf(stderr,"Invalid solution");
		}
		free(colors);
		fprintf(stderr, "%.64lf\n", (double)(end-begin)/CLOCKS_PER_SEC);
		total += ((double) (end - begin)/CLOCKS_PER_SEC);
	}

	total = total/num_runs;

	return total;
}
