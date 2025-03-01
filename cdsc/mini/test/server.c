#include <unistd.h>
#include <stdio.h>
#include <signal.h>



void HNDEL(int i)
{
        printf("i = %d\n",i);
}


int main()
{
        printf("pid : %d\n", getpid());
        struct sigaction sa;
        sa.sa_handler = HNDEL;
        sa.sa_flags = 0;
        printf("[1] = %d\n",sigemptyset(&sa.sa_mask));
        printf("[2] = %d\n",sigaction(SIGUSR1, &sa, NULL));
        while (1)
                pause();
        return 0;
}
