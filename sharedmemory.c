#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

#define SHM_SIZE 1024	

int main()
{
  key_t key = 1234;
   int shmid = shmget(key,SHM_SIZE,IPC_CREAT|0666);
   if(shmid<0)
   {
     perror("shmget");
     exit(1);
   }
   
   char*shmaddr = shmat(shmid,NULL,0);
   if(shmaddr == (char*)-1)
   {
     perror("shmat");
     exit(1);
   }
   
   printf("Enter data to write to shared memory: ");
   fgets(shmaddr,SHM_SIZE,stdin);
   shmdt(shmaddr);
   
   int child_pid = fork();
   if(child_pid == 0)
   {
     char*shmaddr_child = shmat(shmid,NULL,0);
     if(shmaddr_child == (char*)-1)
     {
       perror("shmat");
       exit(1);
     }
       printf("Data read from shared memory: %s ", shmaddr_child);
       shmdt(shmaddr_child);
    }
    else if(child_pid>0)
    {
      wait(NULL);
    }
    else
    {
      perror("fork");
      exit(1);
    }
       shmctl(shmid,IPC_RMID,NULL);
       return 0;
}
