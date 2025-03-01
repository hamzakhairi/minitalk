#include <unistd.h>
#include <stdio.h>
#include <signal.h>



void HNDEL(int i)
{
        put_str("i = %d\n",i);
}


int main()
{
        put_str("pid : %d\n", getpid());
        struct sigaction sa;
        sa.sa_handler = HNDEL;
        sa.sa_flags = 0;
        put_str("[1] = %d\n",sigemptyset(&sa.sa_mask));
        put_str("[2] = %d\n",sigaction(SIGUSR1, &sa, NULL));
        while (1)
                pause();
        return 0;
}
