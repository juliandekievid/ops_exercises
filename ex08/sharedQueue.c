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
data_t thread_CA = {1, "Thread consumer A"}; 

void *producerThread(void *arg); // procucing data to queue 
void *consumerThread(void *arg); // consumes data from queue

pthread_mutex_t lock;

int activeThreads = 0;

queue_t queue = {NULL};

int ctrl_C_pressed = 0;

void sigHandler(int signal);

FILE *FP;


int main()
{
   pthread_t thread_PA_ID, thread_PB_ID, thread_PC_ID, thread_CA_ID;
   struct sigaction act, oldact;

   // Define SHR
   memset(&act, '\0', sizeof(act));
   act.sa_handler = sigHandler;
   act.sa_flags = 0;
   sigemptyset(&act.sa_mask);
   // Install SHR
   sigaction(SIGINT, &act, &oldact);

   pthread_create(&thread_PA_ID, NULL, &producerThread, (void *)&thread_PA);
   pthread_join(thread_PA_ID, NULL);

   pthread_create(&thread_PB_ID, NULL, &producerThread, (void *)&thread_PB);
   pthread_join(thread_PB_ID, NULL);

   pthread_create(&thread_PC_ID, NULL, &producerThread, (void *)&thread_PC);
   pthread_join(thread_PC_ID, NULL);

   pthread_create(&thread_CA_ID, NULL, &consumerThread, NULL);  
   pthread_join(thread_CA_ID, NULL);
   
}

void *producerThread(void *arg){
   //data_t *data = arg;
   while(1)
      {
         data_t *arguments = arg;
         sleep(arguments->intVal);
         pthread_mutex_lock(&lock);
         
      
      if(backQueue(&queue) == NULL){
         createQueue(&queue, *arguments);      
      }else{
         pushQueue(&queue, *arguments);      
      }
         pthread_mutex_unlock(&lock);      
      if(ctrl_C_pressed == 1){
         activeThreads--;
         pthread_exit(NULL);      
      }
      }
}

void *consumerThread(void *arg){
   while(1){
   if(arg == NULL){;}
   sleep(15);   
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
   pthread_mutex_unlock(&lock);

   if(activeThreads <= 0){
      pthread_exit(NULL);
   }      
} 
  return 0;


}

void sigHandler(int signal){
   ctrl_C_pressed = 1;
   printf("Program terminated by Crtl-C\n");
}
