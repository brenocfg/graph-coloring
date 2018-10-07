#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "m_heuristics.h"

#define INF (numv+1)

int cmp_degree (const void * a, const void * b) {
	vertex_t *aa = (vertex_t*) a;
	vertex_t *bb = (vertex_t*) b;
	return bb->degree - aa->degree;
}

uint32_t welsh_powell(uint8_t* graph, uint16_t numv, uint32_t **answer){
	uint32_t croma_n = 0;
	uint8_t *c_used = (uint8_t*) malloc(numv*sizeof(uint8_t));
	vertex_t *vertices = (vertex_t*) malloc(numv*sizeof(vertex_t));

	*answer = (uint32_t*) malloc(numv*sizeof(uint32_t));

	uint32_t *colors = *answer;

	uint32_t i,j;
	for (i = 0; i < numv; i++) {
		vertices[i].index = i;
		vertices[i].degree = 0;
		colors[i] = INF;
		for (j = 0; j < numv; j++) {
			if(graph[i*numv + j]){
				vertices[i].degree++;
			}
		}
	}

	qsort(vertices, numv, sizeof(vertex_t), cmp_degree);

	colors[vertices[0].index] = croma_n++;
	for (i = 1; i < numv; i++) {
		int index = vertices[i].index;
		colors[index] = croma_n;

		memset(c_used,0,numv*sizeof(uint8_t));

		for (j = 0; j < numv; j++) {
			if(graph[index*numv + j] && colors[j] != (uint32_t) INF){
				c_used[colors[j]] = 1;
			}
		}

		for (j = 0; j < croma_n; j++) {
			if(!c_used[j]){
				colors[index] = j;
				break;
			}
		}

		if(colors[index] == croma_n){
			croma_n++;
		}
	}

	return croma_n;
}
