/******************************************************************************
 * File:         displayFunctions.c
 * Version:      1.4
 * Date:         2018-02-20
 * Author:       M. van der Sluys, J.H.L. Onokiewicz, R.B.A. Elsinghorst, J.G. Rouland
 * Description:  OPS exercise 2:  function definitions for display.c
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "displayFunctions.h"
#include "syntaxCheck.h"

// Check the command-line parameters:
ErrCode SyntaxCheck(int argc, char **argv) {
  ErrCode errCode = NO_ERR;
  if(argc != NUM_OF_PARS) {
    errCode = ERR_PARS;
  } else {
    
    if(errCode == NO_ERR) errCode = TestNr(argv[2]);    // Test whether argument 2 contains a positive integer (number of times)
    if(errCode == NO_ERR) errCode = TestNr(argv[3]);    // Test whether argument 3 contains a positive integer (nice value)
  }
  return errCode;
}

// Print an error message:
void DisplayError(ErrCode errCode) {
  switch(errCode) {
  case ERR_PARS:
    printf("\nNumber of command-line parameters is less than four.\n");
    break;
  case ERR_TYPE:
    printf("\nUnknown print type.\n");
    break;
  case ERR_NR:
    printf("\nNumber of times is not a positive integer.\n");
    break;
  case ERR_CHAR:
    printf("\nPrint character contains more than one character.\n");
    break;
  default:
    printf("\nUnknown error code!\n");
  }
  
  printf("\nCorrect syntax:\n");
  printf("  ./display <print type> <number of times> <nice increment> <char 1> <char 2> <char 3>\n\n");
  printf("  first parameter: <print type>: e, p or w\n");
  printf("  second parameter: <number of times>: positive integer\n");
  printf("  third parameter: <nice increment>: positive integer\n");
  printf("  fourth parameter: <char 1>: a single character\n");
  printf("  fifth parameter: <char 2>: a single character\n");
  printf("  parameter: <char 3>: a single character\n");
  printf("\n");  // Newline at end
}

