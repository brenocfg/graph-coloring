CC=gcc
CFLAGS=-O3 -Wextra -Wall -lm

main: common.o m_heuristics.o rnd.o m_metaheuristics.o snt.o
	$(CC) main.c m_heuristics.o common.o rnd.o m_metaheuristics.o snt.o -o tp $(CFLAGS)

m_metaheuristics.o: m_heuristics.o common.o heuristics/matheus/metaheuristics/m_metaheuristics.c heuristics/matheus/metaheuristics/m_metaheuristics.h
	$(CC) -c heuristics/matheus/metaheuristics/m_metaheuristics.c common.o m_heuristics.o -o m_metaheuristics.o $(CFLAGS)

m_heuristics.o: heuristics/matheus/constructive/m_heuristics.c heuristics/matheus/constructive/m_heuristics.h
	$(CC) -c heuristics/matheus/constructive/m_heuristics.c -o m_heuristics.o $(CFLAGS)

rnd.o: heuristics/breno/constructive/rnd.c heuristics/breno/constructive/con.h
	$(CC) -c heuristics/breno/constructive/rnd.c -o rnd.o $(CFLAGS)

snt.o: heuristics/breno/constructive/snt.c heuristics/breno/constructive/con.h
	$(CC) -c heuristics/breno/constructive/snt.c -o snt.o $(CFLAGS)

common.o: common/common.c common/common.h
	$(CC) -c common/common.c -o common.o $(CFLAGS)

clean:
	rm *.o tp
