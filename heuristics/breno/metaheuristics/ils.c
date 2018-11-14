#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "meta.h"

#include "../../matheus/metaheuristics/m_metaheuristics.h"

struct vertex {
	uint32_t id;
	uint32_t degree;
	uint32_t neigh;
};

#define INF (num_ver+1)

int ils_cmp(const void *a, const void *b) {
	struct vertex *va = (struct vertex *) a;
	struct vertex *vb = (struct vertex *) b;

	if (vb->degree - va->degree) {
		return vb->degree - va->degree;
	}

	return va->neigh - vb->neigh;
}

void ils_randomize(uint32_t **array, uint32_t size) {
	if (size <= 1) {
		return;
	}

	uint32_t *a_ptr = *array;

	uint32_t i;
	for (i = 0; i < size-1; i++) {
			int j = i + rand() / (RAND_MAX / (size - i) +1);
			uint32_t tmp = a_ptr[j];
			a_ptr[j] = a_ptr[i];
			a_ptr[i] = tmp;
	}
}


uint32_t ils_snt(uint8_t* graph, uint16_t num_ver, uint32_t **colors) {
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

	qsort(vers, num_ver, sizeof(struct vertex), ils_cmp);

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

uint32_t ils(uint8_t *graph, uint16_t numv, uint32_t **answer) {
	uint8_t it;
	uint32_t best = 9999, cur;
	uint32_t *cand;

	cand = (uint32_t *) malloc(numv*sizeof(uint32_t));

	best = ils_snt(graph, numv, answer);

	for (it = 0; it < 50; ++it) {
		memcpy(cand, *answer, numv*sizeof(uint32_t));
		cur = best;
		ils_randomize(&cand, numv);
		cur = grasp_one_exchange_fixed_penalty(graph, numv, &cand, cur);

		if (cur < best) {
			best = cur;
			memcpy(*answer, cand, numv*sizeof(uint32_t));
		}
	}

	free(cand);

	return best;
}
