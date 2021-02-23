CC=gcc
CFLAGS=-lpthread -lm

NBubble=100000
NMerge=67100000
NShear=5000
NReps=1
printLevel=0
P=4
PMerge=4

.PHONY: clean all

all: mergeSort bubbleSort

mergeSort: mergeSort.c
	$(CC) $? -o $@ $(CFLAGS)

bubbleSort: bubbleSort.c
	$(CC) $? -o $@ $(CFLAGS)

run_mergeSort: mergeSort
	time ./$< $(NMerge) $(PMerge) $(printLevel)

run_bubbleSort: bubbleSort
	time ./$< $(NBubble) $(P) $(printLevel)


clean:
	rm -f two_sorts mergeSort bubbleSort parShear seqShear
