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



void parentProces(void);
void childOneProces(void);
void childTwoProces(void);

char printMethod, printChar, printFirstChar,printSecondChar, printThirdChar;
unsigned long int numOfTimes;
unsigned int niceIncr;
ErrCode err;

int main(int argc, char *argv[]) {
  
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

void childOneProces(void){


   nice(0);
   printChar = printFirstChar;
   PrintCharacters(printMethod, numOfTimes, printChar);  // Print character printChar numOfTimes times using method printMethod
  }

void childTwoProces(void){
   int incr = niceIncr;
   nice(incr);
   printChar = printSecondChar;
   PrintCharacters(printMethod, numOfTimes, printChar);  // Print character printChar numOfTimes times using method printMethod
  }

void parentProcess(void){
   pid_t pid = fork();
   if (pid < 0){
   printf("rror, failed to fork");}
   else if (pid == 0) {childTwoProces();}

   else { 
   int incr = 2*niceIncr;
   nice(incr);
   printChar = printThirdChar;
   PrintCharacters(printMethod, numOfTimes, printChar);  // Print character printChar numOfTimes times using method     printMethod
   wait(NULL);
   wait(NULL);
   //printf(
   }
}
