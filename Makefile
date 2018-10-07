CC=gcc
CFLAGS=-O3 -Wextra -Wall

main: common.o m_heuristics.o
	$(CC) main.c m_heuristics.o common.o -o tp $(CFLAGS)

m_heuristics.o: heuristics/matheus/constructive/m_heuristics.c heuristics/matheus/constructive/m_heuristics.h
	$(CC) -c heuristics/matheus/constructive/m_heuristics.c -o m_heuristics.o $(CFLAGS)

common.o: common/common.c common/common.h
	$(CC) -c common/common.c -o common.o $(CFLAGS)

clean:
	rm *.o tp
