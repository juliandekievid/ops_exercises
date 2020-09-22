# Makefile for ex06
# Use tabs for indentation, not spaces

all: printversion getsignal_sendpid sendsignal_getpid

# Link object files and create a binary executable:
getsignal_sendpid: getsignal_sendpid.o
	gcc -Wall -o getsignal_sendpid getsignal_sendpid.o

sendsignal_getpid: sendsignal_getpid.o
	gcc -Wall -o sendsignal_getpid sendsignal_getpid.o

# Compile C-files and create object file (.o).
# The option -c ensures no linking takes place:
getsignal_sendpid.o: getsignal_sendpid.c
	gcc -c -Wall getsignal_sendpid.c

sendsignal_getpid.o: sendsignal_getpid.c
	gcc -c -Wall sendsignal_getpid.c

clean:
	rm -f *.o

cleanall: clean
	rm -f getsignal_sendpid
	rm -f sendsignal_getpid

printversion:
	gcc --version | grep gcc
