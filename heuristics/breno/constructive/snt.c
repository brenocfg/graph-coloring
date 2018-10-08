#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "con.h"

struct vertex {
	uint32_t id;
	uint32_t degree;
	uint32_t neigh;
};

#define INF (num_ver+1)

int cmp (const void *a, const void *b) {
	struct vertex *va = (struct vertex*) a;
	struct vertex *vb = (struct vertex*) b;

	if(vb->degree - va->degree){
		return vb->degree - va->degree;
	}

	return va->neigh - vb->neigh;
}

uint32_t snt(uint8_t* graph, uint16_t num_ver, uint32_t **colors) {
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

	qsort(vers, num_ver, sizeof(struct vertex), cmp);

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
