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

char printMethod, printChar[3];
unsigned long int numOfTimes;
unsigned int niceValue;
ErrCode err = NO_ERR;


int main(int argc, char *argv[]) {
  
  err = SyntaxCheck(argc, argv);  // Check the command-line parameters
  if(err != NO_ERR) {
    DisplayError(err);        // Print an error message

  } else {
    printMethod = argv[1][0];
    numOfTimes = strtoul(argv[2], NULL, 10);  // String to unsigned long
    niceIncr = strtoul(argv[3], NULL, 10);
    printChar[0] = argv[4][0];
    printChar[1] = argv[5][0];
    printChar[2] = argv[6][0];
  
  
  switch(fork()) {  // parent and child 1 carry out switch()
    case -1: 
        printf("Error, failed to fork"); 
        break;

    case 0:   // Child 1
        nice(niceValue);
        PrintCharacters(printMethod, numOfTimes, printChar[1]);  // Print character printChar numOfTimes times using method printMethod
        break;

    default: 
        switch(fork()){
          case -1:
            printf("rror, failed to fork(1)");
            break;
          case 0:
            nice(2*niceValue);
            PrintCharacters(printMethod, numOfTimes, printChar[2]);  // Print character printChar numOfTimes times using method printMethod
            break;
          default:  // Parent
            nice(0);
            //wait(NULL);
            PrintCharacters(printMethod, numOfTimes, printChar[0]);  // Print character printChar numOfTimes times using method printMethod
            break;
          }
        break;
    }

  printf("\n"); // Newline at end
  }
  
return 0;
}
