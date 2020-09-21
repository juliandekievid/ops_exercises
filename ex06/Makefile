# Makefile for ex06
# Use tabs for indentation, not spaces

all: printversion getsignal getsignal.o

# Link object files and create a binary executable:
getsignal: getsignl.o
	gcc -Wall -o getsignal getsignal.o

sendsignal: sendsignal.o
	gcc -Wall -o sendsignal sendsignal.o

# Compile C-files and create object file (.o).
# The option -c ensures no linking takes place:
getsignal.o: getsignal.c
	gcc -c -Wall getsignal.c

sendsignal.o: sendsignal.c
	gcc -c -Wall sendsignal.c

clean:
	rm -f *.o

cleanall: clean
	rm -f getsignal
	rm -f sendsignal

printversion:
	gcc --version | grep gcc
