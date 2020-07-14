# Makefile for OPS exercise 2
# Use tabs for indentation, not spaces!

all: printversion display

# Link object files and create a binary executable:
display: parent.o displayFunctions.o syntaxCheck.o
	gcc -Wall -o display parent.o displayFunctions.o syntaxCheck.o

# Compile C-files and create object files (.o).
# The option -c ensures no linking takes place:
parent.o: parent.c displayFunctions.h errorCodes.h
	gcc -c -Wall parent.c

displayFunctions.o: displayFunctions.c displayFunctions.h syntaxCheck.h errorCodes.h
	gcc -c -Wall displayFunctions.c

clean:
	rm -f displayFunctions.o parent.o

cleanall: clean
	rm -f display

printversion:
	gcc --version | grep gcc
