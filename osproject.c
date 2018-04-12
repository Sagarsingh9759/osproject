#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

# define MIN_PID 300
# define MAX_PID 5000

int map[5000];
int num=0;
pthread_mutex_t mutex;

int allocate_map()
{
  int j=300;
  while(j<5000)
  {
  map[j]=0;
  j++;
  }
  if(j==5000)
  return 1;
  else
  return -1;
}


int allocate_pid()
{
  int j=300;
  while(j<5000)
  {
    if(map[j]==0)
    {
      map[j]=1;
      return j;
    }
    j++;
  }
  if(j==5000)
  return -1;
}


void release_pid(int pid)
{
	int j=300;
    while(j<305)
    {
      if(pid==j)
      {
        map[j]=0;
        break;
      }
    j++;
	}
    printf("\n  pid released is : %d",pid);
}



void *thread_pid(void *P)
{
   int q=allocate_pid();
   while(num<100)
   {
     pthread_mutex_lock(&mutex);
     if(num >=100)
     {
	   pthread_mutex_lock(&mutex);
       break;
     }
     num++;
     sleep(2);
     printf("%d  ",num);
     pthread_mutex_unlock(&mutex);
    }
   release_pid(q);
}



int main()
{
  int j=0;
  pthread_t thread[100];
  sleep(2);
   
  while(j<100)
  {
    pthread_mutex_init(&mutex,NULL);
    pthread_create(&thread[j],NULL,thread_pid,NULL);
    thread_pid(NULL);
    j++;
  }
  printf("\n");
  
  while(j<100)
  {
    pthread_join(thread[j],NULL);
    pthread_mutex_destroy(&mutex);
    j++;
  }
  
  exit(0);
}
