//	This program will start filter.c and redirect input and output using pipes

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define ESC 0x1B

int main(int argc, char *argv[])
{
  int FDpipeOUT[2];
  int FDpipeIN[2];
  // FD[0] = Read end, FD[1] = Write end

  char buffer;

//	Create pipe
  if(pipe(FDpipeIN) == -1){
    perror("pipe");
    exit(EXIT_FAILURE);
  }
  if(pipe(FDpipeOUT) == -1){
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  
  //	Fork off child process forkFunction
  int forkFun = fork();
  switch(forkFun)
    {
    case -1:
      perror("fork");
	exit(EXIT_FAILURE);

    case 0:		// Cild process
      // Closing unnessesary pipe-ends 
	  close(FDpipeOUT[1]);
      close(FDpipeIN[0]);
      
	  // Redirecting FD 0 to the write side of 
      dup2(FDpipeOUT[0], 0);	// FD 0 -> write side FDpipeOUT
      dup2(FDpipeIN[1], 1);		// FD 1 -> read side FDpipeIN
      
      execlp("./filter", "filter", NULL);
      perror("execlp");
      exit(EXIT_FAILURE);

    default:	// Parent process
      close(FDpipeOUT[0]);
      close(FDpipeIN[1]);

      read(0, &buffer, 1);
      while(1)
      {
	write(FDpipeOUT[1], &buffer, 1);
	read(FDpipeIN[0], &buffer, 1);
	
	// Read pipe from child process filter and writes to stdout parent
	write(1, &buffer, 1);
	read(0, &buffer, 1);
      }
      
	  // Wait for child`
      wait(NULL);
	  
	  // Close pipes
      close(FDpipeOUT[1]);
      close(FDpipeIN[0]);

      exit(EXIT_SUCCESS);
    }
}

