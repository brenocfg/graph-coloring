#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rnd.h"

struct vertex {
	uint32_t id;
	uint32_t degree;
};

#define INF (num_ver+1)

void randomize(struct vertex *array, uint32_t size) {
	if (size <= 1) {
		return;
	}

	uint32_t i;
	for (i = 0; i < size-1; i++) {
			int j = i + rand() / (RAND_MAX / (size - i) +1);
			struct vertex tmp = array[j];
			array[j] = array[i];
			array[i] = tmp;
	}
}

uint32_t rnd(uint8_t* graph, uint16_t num_ver, uint32_t **colors) {
	struct vertex vers[num_ver];
	uint8_t avl_col[num_ver];
	uint32_t answer = 0;

	*colors = (uint32_t*) malloc(num_ver * sizeof(uint32_t));
	uint32_t *c_ptr = *colors;

	/*initialize vertex degrees*/
	uint32_t i, j;
	for (i = 0; i < num_ver; i++) {
		vers[i].id = i;
		vers[i].degree = 0;
		c_ptr[i] = INF;
		for (j = 0; j < num_ver; j++) {
			if(graph[i * num_ver + j]) {
				vers[i].degree += 1;
			}
		}
	}

	/*use constant seed for RNG to reproduce results*/
	srand(0);
	randomize(vers, num_ver);

	/*first vertex gets color 0*/
	c_ptr[vers[0].id] = answer++;

	/*for all other vertices*/
	for (i = 1; i < num_ver; i++) {
		uint32_t index = vers[i].id;
		c_ptr[index] = answer;

		memset(avl_col, 1, num_ver*sizeof(uint8_t));

		for (j = 0; j < num_ver; j++) {
			if(graph[index*num_ver + j] && c_ptr[j] != (uint32_t) INF) {
				avl_col[c_ptr[j]] = 0;
			}
		}

		for (j = 0; j < answer; j++) {
			if(avl_col[j]) {
				c_ptr[index] = j;
				break;
			}
		}

		if (c_ptr[index] == answer) {
			answer++;
		}
	}

	return answer;
}
