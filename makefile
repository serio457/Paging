pager: pager.o Frame.o pageTable.o FIFO.o Page.o
	gcc -o pager pager.o Frame.o pageTable.o FIFO.o Page.o

pager.o: pager.c pager.h
	gcc -c pager.c

Frame.o: Frame.c Frame.h
	gcc -c Frame.c

pageTable.o: pageTable.c pageTable.h
	gcc -c pageTable.c

FIFO.o: FIFO.c FIFO.h
	gcc -c FIFO.c

Page.o: Page.c Page.h
	gcc -c Page.c