#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>

#include <fcntl.h>
#include <string.h>

int count = 0;
void sigHandler(int sig);


int main(int argc, char* argv[], char* envp[])
{
  struct sigaction act, oldact;
  memset(&act, '\0', sizeof(act));
  act.sa_handler = sigHandler;
  act.sa_flags = 0;
  sigemptyset(&act.sa_mask);

  sigaction(25, &act, &oldact);
printf("Program started. Please open ./sendsignal_getpid\n");

  int PID = getpid();
  int fd;

  fd = open("PIDpipe", O_WRONLY);
  write(fd, &PID, sizeof(PID));
  close(fd);


  printf("The ID of the process is: %d\n\n", getpid());
  
//  if(number > '9'){number = '0';}
  
  do 
  {
    char number = '0' + count;
    write(1, &number, 1);
    sleep(1);
  }while(1);

}

//SHR using sa_handler
void sigHandler(int sig)
{
  if(sig == 25)
    {
     count++;
     if(count > 9)
	count = 0;
}
}

