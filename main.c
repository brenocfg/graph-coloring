#include "common/common.h"
#include "heuristics/m_heuristics.h"

int main(int argc, char* argv[]){
	int16_t numv;
	int8_t *graph = read_input(argv[1],&numv);

	run(10,graph,numv,welsh_powell);

	return 0;
}