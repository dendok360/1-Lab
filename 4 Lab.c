   #include <fcntl.h>
    #include <sys/stat.h>
    #include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/fcntl.h>
#include <semaphore.h>

    #define SEM "/my_named_semaphore"
    #define SEM1 "/my_named_semaphore1"
    void logging(){
    FILE *f=fopen("text.txt","a");
    fprintf(f, "Logging by process with id %d\n", getpid());
    fclose(f);
    }

    int main(int argc, char ** argv) {
    sem_t *sem;
    sem_t *sem1;
    
    if ( (sem1 = sem_open(SEM1, O_CREAT, 0777, 1)) == SEM_FAILED ) {
    logging();
    return 1;
    }
    if ( (sem = sem_open(SEM, O_CREAT, 0777, 0)) == SEM_FAILED ) {
    logging();
    return 1;
    }
	int pid=fork();
    if(!pid){
    for(int i;i<10;i++){
    sem_wait(sem);
    logging();
    sem_post(sem1); 
    }   
    }else{
    for(int i;i<10;i++){
    sem_wait(sem1);
   logging();
    sem_post(sem);
    }	
    }
  sem_unlink(SEM1);
  sem_unlink(SEM);
    return 0;
    }


