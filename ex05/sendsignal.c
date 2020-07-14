//program to send a signal every 3 seconds to the process getsignal

#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  unsigned long int getsignalPID = strtoul(argv[1], NULL, 10);
  printf("PID of getsignal = %ld\n", getsignalPID);

  while(1)
    {
      kill(getsignalPID, 25);
      sleep(3);
    }
}
