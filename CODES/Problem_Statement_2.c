#include <stdio.h>
#include<stdlib.h>


int main()
{
    printf("Parent Process --> PID : %d \n",getpid());
    int child = fork();
    if(child == 0)
    {
        printf("Child Process(Before Parent's Execution) --> PID : %d\t PPID : %d \n",getpid(),getppid());
        sleep(5);
        printf("Child Process(After Parent's Execution) --> PID : %d\t PPID : %d \n",getpid(),getppid());
        printf("\n\nChild Process has become ORPHAN PROCESS\n\n");
        int grandchild = fork() ;
        if(grandchild == 0)
        {
            printf("Grand Child Process --> PID : %d\t PPID : %d \n",getpid(),getppid());
            printf("Grandchild Process Completed its Execution\n\n");
            printf("Grandchild Process has entered the Zombie State\n\n");
        }
        else
        {
            sleep(4);
            printf("Grandchild Process was removed from Zombie State by its parent\n");
            printf("Child Process --> PID : %d\t PPID : %d \n",getpid(),getppid());

        }
        

    }
    else
    {
        sleep(1) ;
        printf("Parent Process Executed Successfully\n\n");
    }
    return 0;
    
}