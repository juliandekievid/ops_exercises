#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int count = 0;
void sigHandler(int sig);
int fd;

int main(int argc, char* argv[], char* envp[])
{
  struct sigaction act;
  act.sa_handler = &sigHandler;
  sigaction(25, &act, NULL);
printf("Program started. Please open ./sendsignal_getpid\n");

  int PID = getpid();


  fd = open("PIDpipe", O_WRONLY);
  write(fd, &PID, sizeof(PID));
  close(fd);


  printf("PID: %d\n", getpid());
  
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
     if(count > 9){
	count = 0;
}
}
}
