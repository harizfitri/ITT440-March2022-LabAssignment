#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
        int p2c[2];
        int res = pipe(p2c);
        if(res == -1)
        {
                perror("pipe(p2c) error: ");
                exit(EXIT_FAILURE);
        }
        int pid = fork();
        if(pid == -1){
                perror("fork() error");
                exit(EXIT_FAILURE);
        }

        if(pid == 0)
        {
                close(p2c[1]);
                while(1)
                {
                        int a;
                        read(p2c[0], &a, sizeof(int));
                        printf("[In CHILD] : %d\n",a);
                        if(a==0)
                                break;
                        else{
                        int ok = 1;
                        if(a<2)
                        {
                                ok = 0;
                        }
                        for(int d=2;d*d<=a && ok == 1; d++)
                        {
                                if(a%d==0)
                                        ok=0;
                        }
                        if(ok == 1){
                                printf("Prime");}
                        else{
                                printf("Not prime");}
                        }

                }
                close(p2c[0]);
                exit(EXIT_SUCCESS);
        }
        else{
        close(p2c[0]);
        while(1)
        {
                int a;
                printf("[In PARENT]: ");
                scanf("%d", &a);

                write(p2c[1], &a, sizeof(int));
                if(a==0)
                        break;
                sleep(3);
        }
        int status;
        wait(&status);

        printf("\n[In PARENT] Child has finished with exit status: %d\n", status);
        close(p2c[1]);
        }

        return 0;
}
