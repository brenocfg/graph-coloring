#include "m_metaheuristics.h"
#include "../constructive/m_heuristics.h"

#define INF (numv+1)

uint32_t check_conflicts(uint32_t v, uint32_t color, uint8_t* graph, uint32_t* colors, uint16_t numv){
	uint32_t i,old_conflicts=0,new_conflicts=0;

	for (i = 0; i < numv; i++) {
		if(graph[v*numv + i] && colors[i] == colors[v]){
			old_conflicts++;
		}

		if(graph[v*numv + i] && colors[i] == color){
			new_conflicts++;
		}
	}

	return old_conflicts-new_conflicts;
}

void reduce_colors(uint8_t* graph,uint32_t **candidate, uint16_t numv, uint32_t croma_n){
	uint32_t *colors = *candidate;
	uint32_t remove = rand() % croma_n;
	uint32_t i,j;
	uint32_t *c_used = (uint32_t*) malloc(croma_n*sizeof(uint32_t));
	uint32_t min = 0;

	for(i = 0; i < numv; i++){
		if(colors[i]==remove){
			memset(c_used,0,croma_n*sizeof(uint32_t));

			for(j = 0; j < numv; j++){
				if(graph[i*numv+j] && colors[i]!=remove){
					c_used[colors[j]]++;
				}
			}

			if(min == remove)
				min++;

			for(j=0; j<croma_n ; j++){
				if(j!=remove && c_used[j]<c_used[min]){
					min = j;
				}
			}

			colors[i] = min;
		}
	}

	for(i = 0; i < numv; i++){
		if(colors[i]>remove){
			colors[i]--;
		}
	}


}

void fixed_penalty_local_search(uint8_t* graph,uint32_t** candidate, uint16_t numv, uint32_t croma_n){
	//uint32_t n_conflicts = 0;
	uint32_t i,j;
	uint8_t improve = 1;
	uint32_t *colors = *candidate;
	uint32_t **mem = (uint32_t**) malloc(numv*sizeof(uint32_t*));

	for (i = 0; i < numv; i++) {
		mem[i] = (uint32_t*) malloc(croma_n*sizeof(uint32_t));
		for(j=0; j < croma_n; j++){
			mem[i][j] = 0;
		}
	}

	for (i = 0; i < numv; i++){
		for (j = 0; j < numv; j++){
			if(graph[i*numv + j]){
				mem[i][colors[j]]++;
			}
		}
	}


	while(improve){
		improve = 0;
		uint32_t best_v;
		uint32_t best_c;
		int32_t best_r = -9999;

		for(i = 0; i < croma_n; i++){
			for(j = 0; j < numv; j++){
				int32_t res = mem[j][colors[j]]-mem[j][i];
				if(res>best_r){
					best_r = res;
					best_v = j;
					best_c = i;
				}

				if(res>0){
					improve = 1;
				}
			}
		}

		if(!improve)
			break;

		for (i = 0; i < numv; i++) {
			if(graph[i*numv + best_v]){
				mem[i][colors[best_v]]--;				
				mem[i][best_c]++;
			}
		}
		colors[best_v] = best_c;
	}

	for (i = 0; i < numv; i++) {
		free(mem[i]);
	}

	free(mem);
}

uint32_t one_exchange_fixed_penalty(uint8_t* graph, uint16_t numv, uint32_t **answer){
	uint32_t croma_n = 0;
	uint32_t *candidate = (uint32_t*) malloc(numv*sizeof(uint32_t));
	uint32_t actual_penalty = 0;

	croma_n = welsh_powell_brtiebreak(graph,numv,answer);

	uint32_t *colors = *answer;

	memcpy(candidate,colors,numv*sizeof(uint32_t));

	while(!check_solution(graph,numv,candidate)){
			
		memcpy(colors,candidate,numv*sizeof(uint32_t));

		reduce_colors(graph,&candidate,numv,croma_n);

		croma_n--;
		
		if(check_solution(graph,numv,candidate)){
			fixed_penalty_local_search(graph,&candidate,numv,croma_n);
		}
	}

	free(candidate);

	return ++croma_n;
}

uint32_t grasp_one_exchange_fixed_penalty(uint8_t* graph, uint16_t numv, uint32_t **answer, uint32_t c_n){
	uint32_t croma_n = c_n;
	uint32_t *candidate = (uint32_t*) malloc(numv*sizeof(uint32_t));
	uint32_t actual_penalty = 0;

	uint32_t *colors = *answer;

	memcpy(candidate,colors,numv*sizeof(uint32_t));

	do {
		memcpy(colors,candidate,numv*sizeof(uint32_t));
		reduce_colors(graph,&candidate,numv,croma_n);

		croma_n--;
		
		if(check_solution(graph,numv,candidate)){
			fixed_penalty_local_search(graph,&candidate,numv,croma_n);
		}
	}while(!check_solution(graph,numv,candidate));

	free(candidate);

	return ++croma_n;
}

int cmp_deg(const void * a, const void * b) {
	vertex_t *aa = (vertex_t*) a;
	vertex_t *bb = (vertex_t*) b;
	return bb->degree - aa->degree;
}

uint32_t rand_welsh_powell(uint8_t* graph, uint16_t numv, uint32_t **answer){
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

	int alpha = rand() % (int) ceil(0.5*numv);

	qsort(vertices+alpha, numv-alpha, sizeof(vertex_t), cmp_deg);

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

uint32_t grasp(uint8_t* graph, uint16_t numv, uint32_t **answer){
	uint8_t it;
	uint32_t c_n;
	uint32_t *candidate;

	uint32_t best = one_exchange_fixed_penalty(graph, numv, answer);

	for(it = 0; it < 20; it++){
		c_n = rand_welsh_powell(graph,numv,&candidate);
		c_n = grasp_one_exchange_fixed_penalty(graph,numv,&candidate,c_n);
		
		if(c_n<best){
			best = c_n;
			memcpy(*answer,candidate,numv*sizeof(uint32_t));
		}

		free(candidate);
	}

	return best;
}
