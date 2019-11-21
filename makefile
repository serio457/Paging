pager: pager.o pageTable.o FIFO.o LRU.o MFU.o Random.o Page.o
	gcc -o pager pager.o pageTable.o FIFO.o LRU.o MFU.o Random.o Page.o

pager.o: pager.c pager.h
	gcc -c pager.c

pageTable.o: pageTable.c pageTable.h
	gcc -c pageTable.c

FIFO.o: FIFO.c FIFO.h
	gcc -c FIFO.c

LRU.o: LRU.c LRU.h
	gcc -c LRU.c

MFU.o: MFU.c MFU.h
	gcc -c MFU.c

Random.o: Random.c Random.h
	gcc -c Random.c

Page.o: Page.c Page.h
	gcc -c Page.c