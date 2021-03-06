/******************************************************************************
 * File:         syntaxCheck.c
 * Version:      1.4
 * Datum:        2018-02-20
 * Author:       M. van der Sluys, J.H.L. Onokiewicz, R.B.A. Elsinghorst, J.G. Rouland
 * Description:  OPS exercise 2:  definitions of test functions for display.c
 ******************************************************************************/

#include <stdlib.h>
#include "syntaxCheck.h"
#include "string.h"

// Test whether an argument is one character long and has the correct value (e,p,w):
ErrCode TestType(char *printMethod) {
  ErrCode fout = NO_ERR;
  
   int length = strlen(printMethod);
   if (length == 1) {   
      if ((printMethod[0] == 'e') || (printMethod[0] == 'p') || (printMethod[0] == 'w')) {
      fout = NO_ERR;
      }else {fout = ERR_TYPE;}

   }else {fout = ERR_TYPE;}
   
  return fout;
}


// Test whether an argument contains a non-negative number:
ErrCode TestNr(char *numberOfTimes) {
  ErrCode fout = NO_ERR;
  
   int length = strlen(numberOfTimes);
   for(int i = 0; i < length;){
   if(numberOfTimes[i] == '-')
      {fout = ERR_NR;}
   else {fout = NO_ERR;}
   i++;
   break;
}

  
  return fout;
}


// Test whether an argument contains only one character:
ErrCode TestChar(char *printChar) {
  ErrCode fout = NO_ERR;
  
   int length = strlen(printChar);
   if(length != 1){
   fout = ERR_CHAR;
   }
   else{fout = NO_ERR;}
  
  return fout;
}
