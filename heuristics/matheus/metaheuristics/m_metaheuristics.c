#include "m_metaheuristics.h"

uint32_t check_conflicts(uint32_t v, uint32_t color, uint8_t* graph, uint32_t* colors, uint16_t numv){
	uint32_t i,old_conflicts=0,new_conflicts=0;

	for (i = 0; i < numv; i++) {
		if(graph[v*numv + i] && colors[i] == colors[v]){
			old_conflicts++;
		}
	}

	for (i = 0; i < numv; i++) {
		if(graph[v*numv + i] && colors[i] == color){
			new_conflicts++;
		}
	}

	return old_conflicts-new_conflicts;
}

void reduce_colors(uint32_t **candidate, uint16_t numv, uint32_t croma_n){
	uint32_t *colors = *candidate;
	uint32_t remove = rand() % croma_n;
	uint32_t i;

	for(i = 0; i < numv; i++){
		if(colors[i]>remove){
			colors[i]--;
		}else if(colors[i]==remove){
			colors[i] = rand() % (croma_n-1);
		}
	}
}

void fixed_penalty_local_search(uint8_t* graph,uint32_t** candidate, uint16_t numv, uint32_t croma_n){
	uint32_t n_conflicts = 0;
	uint32_t i,j;
	uint8_t improve = 1;
	uint32_t *colors = *candidate;

	for (i = 0; i < numv; i++) {
		for (j = 0; j < numv; j++) {
			if(graph[i*numv + j] && colors[i] == colors[j]){
				n_conflicts++;
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
				int32_t res = check_conflicts(j, i, graph, colors, numv);
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

		colors[best_v] = best_c;
	}
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

		reduce_colors(&candidate,numv,croma_n);

		croma_n--;
		
		if(check_solution(graph,numv,candidate)){
			fixed_penalty_local_search(graph,&candidate,numv,croma_n);
		}
	}

	return ++croma_n;
}