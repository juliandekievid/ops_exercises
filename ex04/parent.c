/******************************************************************************
 * File:         display.c
 * Version:      1.4
 * Date:         2018-02-20
 * Author:       M. van der Sluys, J.H.L. Onokiewicz, R.B.A. Elsinghorst, J.G. Rouland
 * Description:  OPS exercise 2: syntax check
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "displayFunctions.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

ErrCode err = NO_ERR;

int main(int argc, char *argv[]) {
  
  err = SyntaxCheck(argc, argv);  // Check the command-line parameters
  if(err != NO_ERR) {
    DisplayError(err);        // Print an error message  
  } else {
    int niceValue = strtoul(argv[3], NULL, 10);
    switch(fork())  //Parent and child 1 carry out switch()
      {
      case -1: 
	printf("Error, failed to fork(1)"); 
	break;
      case 0: //Child one
	nice(niceValue);
	execl("../ex02/display", "display", argv[1], argv[2], argv[4], (char *) NULL);
	printf("Starting child 1 failed\n");
	exit(1);
	break;
      default:  //Parent
	switch(fork())
	  { //create child 2
	  case -1:
	    printf("Error, failed to fork(2)"); 
	    break;
	  case 0:
	    nice(2*niceValue);
	    execl("../ex02/display", "display",  argv[1], argv[2], argv[5], (char *) NULL);
	    printf("Starting child 2 failed\n");
	    exit(1);
	    break;
	  default:
	    switch(fork()){ // Create child 3
	    case -1: 
	      printf("Error, failed to fork(3)"); 
	      break;
	    case 0: // Child 3
	      nice(0);
	      execl("../ex02/display", "display",  argv[1], argv[2], argv[6], (char *) NULL);
	      printf("Starting child 3 failed\n");
	      exit(1);
	      break;
	    default:
	      break;
	    }  
	  }
	
	wait(NULL);
	wait(NULL);
	wait(NULL);
	printf("All children have finished\n");
	printf("\n");  // Newline at end
	break;	 
      }
  }
  
  return 0;
}

