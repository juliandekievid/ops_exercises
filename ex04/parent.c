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

//char printMethod, printChar, printFirstChar,printSecondChar, printThirdChar;
//unsigned long int numOfTimes;

ErrCode err = NO_ERR;

int main(int argc, char *argv[]) {
  
  err = SyntaxCheck(argc, argv);  // Check the command-line parameters
  if(err != NO_ERR) {
    DisplayError(err);        // Print an error message  
  
  } else {
   // numOfTimes = strtoul(argv[2], NULL, 10);  // String to unsigned long
  niceValue = strtoul(argv[3], NULL, 10);
  printf("\n");  // Newline at end

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
      switch(fork()){ //create child 2
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
              wait(NULL);
              wait(NULL);
              break;
          }   
          break;
   }
      break;
  }

return 0;
}

