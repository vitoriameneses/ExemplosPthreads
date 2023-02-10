/* Arquivo:  
 *    pth_semaphore2.c
 *
 * Propósito:
 *    Exemplificar o uso de semáforo como limitador do número
 *    de threads que executa paralelamente.
 *
 *
 * Compile:  gcc -g -Wall -o pth_semaphore3 pth_semaphore3.c -lpthread -lrt
 * Usage:    ./pth_semaphore3 
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <semaphore.h>
#include <time.h>
#include <unistd.h>

sem_t semaphore; 

void *execute(void *args) {
   long id = (long) args;
   printf("Thread %ld running\n", id);
   sleep((rand() % 5) + 1); //threads vão "dormir" de 1 a 5 segundos
   printf("Thread %ld finish\n", id);
   sem_post(&semaphore);
   return NULL;
} 


/*--------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
   long       thread;  /* Use long in case of a 64-bit system */
   pthread_t* thread_handles; 
   srand(0);
   
   sem_init(&semaphore, 0, 4); //4 threads por vez
   
   long thread_count = 40; 

   thread_handles = malloc (thread_count*sizeof(pthread_t)); 

   for (thread = 0; thread < thread_count; thread++){  //vai criar as 40 threads
      sem_wait(&semaphore); //antes de criar, chama sem_wait
      //processo principal esperando para criar a proxima thread
      pthread_create(&thread_handles[thread], NULL, execute, (void*) thread);  
   }
   
   printf("Hello from the main thread\n");
   //sleep(10);
   for (thread = 0; thread < thread_count; thread++){ 
      pthread_join(thread_handles[thread], NULL); // Bloqueante
      printf("Thread %ld joined!\n", thread);
   }
   
   free(thread_handles);
   sem_destroy(&semaphore);
   printf("Main thread exit\n");
   return 0;
}  /* main */


