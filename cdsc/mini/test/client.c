#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>



int main(int argc, char *argv[])
{   
    int pid = atoi(argv[1]);
    if (kill(pid, SIGUSR1) == -1)
    {
        printf("filde sent signal\n");
    }
    printf("secsses sent signal\n");
    return 0;
}

