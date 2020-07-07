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

void parentProces(void);
void childOneProces(void);
void childTwoProces(void);

int main(int argc, char *argv[]) {
  char printMethod, printFirstChar,printSecondChar, printThirdChar;
  unsigned long int numOfTimes;
  unsigned int niceIncr;
  ErrCode err;
  
  err = SyntaxCheck(argc, argv);  // Check the command-line parameters
  if(err != NO_ERR) {
    DisplayError(err);        // Print an error message
  } else {
    printMethod = argv[1][0];
    numOfTimes = strtoul(argv[2], NULL, 10);  // String to unsigned long
    niceIncr = argv[3][0];
    printFirstChar = argv[4][0];
    printSecondChar = argv[5][0];
    printThirdChar = argv[6][0];
    
    PrintCharacters(printMethod, numOfTimes, printChar);  // Print character printChar numOfTimes times using method printMethod
  }
  
  printf("\n");  // Newline at end

   pid_t pid = fork();
   switch(pid)
   {
   case -1: printf("Error, failed to fork"); 
      break;
   case 0: childOneProces(); 
      break;
   default: parentProces();
   }
  return 0;
}
