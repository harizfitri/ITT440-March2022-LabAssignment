#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void childTask(){
    char name[20];
    printf("Enter name : ");
    fgets(name, sizeof(name), stdin);
    printf("\nMy name is ");
    puts(name);
    printf("My child process => PPID=%d, PID=%d\n\n", getppid(), getpid());
exit(0);
}

void parentTask(){
     printf("Phild process => PID=%d\n", getpid());
     printf("All child process is finished!\n");
     printf("Job is done\n");
}

void waiting(){
     printf("Waiting for child process to finished...");
     wait(NULL);
     printf("\nChild process finished");
     printf("___________________________________________________________\n");
}

int main(void){
    for(int i = 1; i <5; i++){
        pid_t pid = fork();
        if(pid == 0){
            childTask();
        }else if(i == 4){
            waiting();
            parentTask();
        }else waiting();
    }
    return EXIT_SUCCESS;
}
