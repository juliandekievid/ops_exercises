/******************************************************************************
 * File:         main.c
 * Version:      1.2
 * Date:         2017-10-18
 * Author:       J. Onokiewicz, M. van der Sluys
 * Description:  OPS exercise 5: Queues
 ******************************************************************************/

#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>

data_t thread_PA = {2, "Thread producer A"}; // writes data to queue every 2 seconds
data_t thread_PB = {3, "Thread producer B"}; // writes data to queue every 3 seconds
data_t thread_PC = {4, "Thread procuder C"}; // writes data to queue every 4 seconds
data_t thread_CA = {}; 

void *producerThread(void *arg); // procucing data to queue 
void *consumerThread(void *arg); // consumes data from queue
queue_t queue = {NULL};
pthread_mutex_t lock;

int activeThreads = 0;

int ctrl_C_pressed = 0;

void sigHandler(int signal);

FILE *FP;


int main()
{
   pthread_mutex_init(&lock, NULL);   
   struct sigaction act, oldact;
   // Define SHR
   memset(&act, '\0', sizeof(act));
   act.sa_handler = sigHandler;
   act.sa_flags = 0;
   sigemptyset(&act.sa_mask);
   // Install SHR
   sigaction(SIGINT, &act, &oldact);

   pthread_t thread_ID;
   pthread_create(&thread_ID, NULL, &producerThread, (void *)&thread_PA);
   pthread_create(&thread_ID, NULL, &producerThread, (void *)&thread_PB);
   pthread_create(&thread_ID, NULL, &producerThread, (void *)&thread_PC);
   pthread_create(&thread_ID, NULL, &consumerThread, (void *)&thread_CA);
   pthread_join(thread_ID, NULL);
   pthread_mutex_destroy(&lock);

   return 0;
}

void *producerThread(void *arg){
   
   //data_t *data = arg;
   activeThreads++;
   
   data_t *arguments = arg;
   while(1)
      {
  //       printf("active threads: %d\n",activeThreads);         
         sleep(arguments->intVal);
         pthread_mutex_lock(&lock);
        
      
      if(sizeQueue(&queue) == 0){
         createQueue(&queue, *arguments);  
        
      }else{
         pushQueue(&queue, *arguments);      
      }
      pthread_mutex_unlock(&lock);             

      if(ctrl_C_pressed == 1){
         activeThreads--;
//         printf("thread closed. active threads: %d\n", activeThreads);                  
         pthread_exit(NULL);       
         
      }
      }   
}

void *consumerThread(void *arg){
  while(1){
   if(arg == NULL){;}
  sleep(15);   
//   printf("15 seconds counter\nactive threads: %d\n\n", activeThreads);
   pthread_mutex_lock(&lock);
   FP = fopen("queue.txt", "w");
 
   showQueue(&queue);
   const node_t* nextN = queue.lastNode;

   if(nextN == NULL){
      fprintf(FP, "Queue is empty, last node is %p\n", (void*) queue.lastNode);
   }else{
      fprintf(FP, "Queue contains %ld nodes:\n", sizeQueue(&queue));
      fprintf(FP, "Last node: %p\n", (void*) queue.lastNode);
      do {
         nextN = nextN->nextNode;
         fprintf(FP, "pNode = %p  Data = '%d' '%s'  nextN = %p\n", 
                (void*)nextN, nextN->data.intVal, nextN->data.text, (void*)nextN->nextNode);      
      }while(nextN != queue.lastNode);      
   }
   fclose(FP);
   deleteQueue(&queue);
 //  printf("\n\n\n\n\n\n\n\n");
   pthread_mutex_unlock(&lock);

   if(activeThreads <= 0){
      pthread_exit(NULL);
     
   }      
}
}

void sigHandler(int signal){
   ctrl_C_pressed = 1;
   printf("Program terminated by Crtl-C\n");
}
