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



void parentProces(char *argv[]);
void childOneProces(char *argv[]);
void childTwoProces(char *argv[]);
void childThreeProces(char *argv[]);


char printMethod, printChar, printFirstChar,printSecondChar, printThirdChar;
unsigned long int numOfTimes;
unsigned int niceIncr;
ErrCode err = NO_ERR;

int main(int argc, char *argv[]) {
  
  err = SyntaxCheck(argc, argv);  // Check the command-line parameters
  if(err != NO_ERR) {
    DisplayError(err);        // Print an error message  
  
  } else {
   // numOfTimes = strtoul(argv[2], NULL, 10);  // String to unsigned long
  niceValue = strtoul(argv[3], NULL, 10);
  printf("\n");  // Newline at end

  //pid_t pid = ;
  switch(fork())  //Parent and child 1 carry out switch()
  {
  case -1: 
      printf("Error, failed to fork"); 
      break;
  case 0: //Child one
      nice(niceValue);
      execl("../ex02/display", "display", argv[1], argv[2], argv[4], (char *) NULL);
      printf("Starting child failed\n");
      exit(1);
      break;
  default: parentProces(argv); //Parent
      switch(fork()){ //create child 2
      
      
      }
      
      pid_t pid = fork();
   if (pid < 0){
   printf("rror, failed to fork");}
   else if (pid == 0) {childTwoProces(argv);}
   pid = fork();
   if (pid < 0) {
   printf("rror, failed to fork");}
   else if (pid == 0) {childThreeProces(argv);}
   
   wait(NULL);
   wait(NULL);
   wait(NULL);
  }

return 0;
}

void childOneProces(char *argv[]){
  //printf("Child one");
  nice(0);
  execl("../ex02/display", "display", argv[1], argv[2], argv[4], (char *) NULL);
  perror("ChildOne");
 }

void childTwoProces(char *argv[]){
   int incr = niceIncr;
   nice(incr);
  //printf("Child one");
  execl("../ex02/display", "display",  argv[1], argv[2], argv[5], (char *) NULL);
  perror("ChildTwo");   
}

void childThreeProces(char *argv[]){
  //printf("Child three");
  int incr = niceIncr * 2;
  nice(incr);
 execl("../ex02/display", "display",  argv[1], argv[2], argv[6], (char *) NULL);
  perror("ChildThree");
}

void parentProces(char *argv[]){
   pid_t pid = fork();
   if (pid < 0){
   printf("rror, failed to fork");}
   else if (pid == 0) {childTwoProces(argv);}
   pid = fork();
   if (pid < 0) {
   printf("rror, failed to fork");}
   else if (pid == 0) {childThreeProces(argv);}
   
   wait(NULL);
   wait(NULL);
   wait(NULL);
   //printf(
}
