//program to send a signal every 3 seconds to the process getsignal

#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
  int fd;
  pid_t PID;
  fd = open("PIDpipe" , O_RDONLY);
  read(fd, &PID, sizeof(PID));

  close(fd);    
  printf("PID of getsignal = %d\n",PID);

  while(1)
    {
      kill(PID, 25);
      sleep(3);
    }
}
