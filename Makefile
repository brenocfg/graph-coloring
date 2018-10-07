CC=gcc
CFLAGS=-O3

main: common.o m_heuristics.o
	$(CC) main.c m_heuristics.o common.o -o tp.out $(CFLAGS)

m_heuristics.o: heuristics/m_heuristics.c heuristics/m_heuristics.h
	$(CC) -c heuristics/m_heuristics.c -o m_heuristics.o $(CFLAGS)

common.o: common/common.c common/common.h
	$(CC) -c common/common.c -o common.o $(CFLAGS)

clean:
	rm *.o tp.out