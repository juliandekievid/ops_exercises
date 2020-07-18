#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char number = '1';
void sigHandler(int sig);
int fd;

int main(void)
{
  struct sigaction act, oldact;

  //define SHR;
  memset(&act, '\0', sizeof(act));
  act.sa_handler = sigHandler;
  act.sa_flags = 0;
  sigemptyset(&act.sa_mask);

  //install SHR
  sigaction(25, &act, &oldact);

  pid_t PID = getpid();


  fd = open("PIDpipe", O_WRONLY);
  write(fd, &PID, sizeof(PID));
  close(fd);

  unlink("PIDfifo");
  printf("PID: %d\n", PID);
  
  if(number > '9'){number = '0';}
  
  while(1){
    write(1, &number, 1);
    sleep(1);
  }
  return 0;
}

//SHR using sa_handler
void sigHandler(int sig)
{
  printf("\nsignal caught: %d\n", sig);
  number++;
}
