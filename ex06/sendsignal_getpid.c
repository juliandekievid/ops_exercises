//program to send a signal every 3 seconds to the process getsignal

#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[], char* envp[])
{
  int fd;
  int PID;
printf("Program started. Please open ./getsignal_sendpid\n");
//  pid_t PID = getpid();
  fd = open("PIDpipe" , O_RDONLY);
  read(fd, &PID, sizeof(PID));
  close(fd);    
  printf("Starting sending kill commands to PID = %i\n",PID);
  do 
	{
	sleep(3); //sleep for 3 sec
	kill(PID, 25);
	printf("Kill is sent to PID = %i\n",PID);
	}
  while(!kill(PID, 0));
    printf("Proces %i is stopped. Quit application\n",PID);

    
}
