#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "meta.h"

#define INF (num_ver+1)

struct vertex {
	uint32_t id;
	uint32_t degree;
	uint32_t neigh;
};

int sa_cmp(const void *a, const void *b) {
	struct vertex *va = (struct vertex *) a;
	struct vertex *vb = (struct vertex *) b;

	if (vb->degree - va->degree) {
		return vb->degree - va->degree;
	}

	return va->neigh - vb->neigh;
}

uint32_t sa_snt(uint8_t* graph, uint16_t num_ver, uint32_t **colors) {
	struct vertex vers[num_ver];
	uint8_t avl_col[num_ver];
	uint32_t answer = 0;

	*colors = (uint32_t*) malloc(num_ver*sizeof(uint32_t));
	uint32_t *c_ptr = *colors;

	/*initialize vertex degrees and neighborhoods*/
	uint32_t i,j;
	for (i = 0; i < num_ver; i++) {
		vers[i].id = i;
		vers[i].degree = 0;
		c_ptr[i] = INF;
		for (j = 0; j < num_ver; j++) {
			if(graph[i*num_ver + j]){
				vers[i].degree++;
			}
		}
	}
	
	for (i = 0; i < num_ver; i++) {
		vers[i].neigh = 0;
		for (j = 0; j < num_ver; j++) {
			if(graph[i*num_ver + j]) {
				vers[i].neigh += vers[j].degree-1;
			}
		}
	}

	qsort(vers, num_ver, sizeof(struct vertex), sa_cmp);

	c_ptr[vers[0].id] = answer++;

	for (i = 1; i < num_ver; i++) {
		uint32_t index = vers[i].id;
		c_ptr[index] = answer;

		memset(avl_col, 1, num_ver*sizeof(uint8_t));

		for (j = 0; j < num_ver; j++) {
			if(graph[index*num_ver + j] && c_ptr[j] != (uint32_t) INF){
				avl_col[c_ptr[j]] = 0;
			}
		}

		for (j = 0; j < answer; j++) {
			if(avl_col[j]){
				c_ptr[index] = j;
				break;
			}
		}

		if(c_ptr[index] == answer) {
			answer++;
		}
	}

	return answer;
}

uint32_t eval(uint8_t *graph, uint32_t *colors, uint16_t numv) {
	uint32_t conf = 0;

	uint32_t i, j;
	for (i = 0; i < numv; i++) {
		for (j = i+1; j < numv; j++) {
			if (i == j) {
				continue;
			}
			if (graph[i * numv + j] && colors[i] == colors[j]) {
				conf++;
			}
		}
	}

	return conf;
}

void gen_rand(uint32_t **colors, uint16_t numv, uint16_t k) {
	uint16_t i;

	uint32_t *c_ptr = *colors;
	for (i = 0; i < numv; i++) {
		c_ptr[i] = rand() % k;
	}
}

void gen_new(uint8_t *graph, uint32_t **colors, uint16_t numv, uint32_t numc) {
	uint32_t i, j;
	uint32_t *c_ptr;

	uint32_t mem[numv][numc];

	c_ptr = *colors;

	for (i = 0; i < numv; i++) {
		for (j = 0; j < numc; j++) {
			mem[i][j] = 0;
		}
	}

	for (i = 0; i < numv; i++) {
		for (j = 0; j < numv; j++) {
			if(graph[i*numv + j]) {
				mem[i][c_ptr[j]]++;
			}
		}
	}

	uint32_t best_v;
	uint32_t best_c;
	int32_t best_r = -9999;

	for (i = 0; i < numc; i++) {
		for (j = 0; j < numv; j++) {
			int32_t res = mem[j][c_ptr[j]] - mem[j][i];
			if (res > best_r) {
				best_r = res;
				best_v = j;
				best_c = i;
			}
		}
	}

	if (best_r != 0) {
		c_ptr[best_v] = best_c;
	}

	else {
		c_ptr[rand() % numv] = rand() % numc;
	}
}

uint32_t sa(uint8_t *graph, uint16_t numv, uint32_t **answer) {
	uint32_t best;

	uint32_t *cand, *best_a;

	cand = (uint32_t *) malloc(numv*sizeof(uint32_t));
	best_a = (uint32_t *) malloc(numv*sizeof(uint32_t));

	best = sa_snt(graph, numv, answer);

	gen_rand(&best_a, numv, best-1);
	uint32_t best_con = eval(graph, best_a, numv);

	uint32_t temp = 50;

	uint16_t it;
	uint8_t change = 1;
	while (change) {
		change = 0;
		for (it = 0; it < 100; ++it) {
			memcpy(cand, best_a, numv*sizeof(uint32_t));
			gen_new(graph, &cand, numv, best-1);

			uint32_t new_con = eval(graph, cand, numv);
			int32_t delta = best_con - new_con;

			if (temp == 0) {
				break;
			}

			uint32_t prob = 1000/temp;

			if (delta > 0 || ((rand() % 1000) > prob)) {
				memcpy(best_a, cand, numv*sizeof(uint32_t));
				best_con = new_con;
				change = 1;
				if (new_con == 0) {
					best--;
					memcpy(*answer, best_a, numv*sizeof(uint32_t));
					gen_rand(&best_a, numv, best-1);
				}
			}
		}
		temp--;
	}


	return best;
}
