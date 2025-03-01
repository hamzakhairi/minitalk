#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void handle_signal(int sig, siginfo_t *info, void *context)
{
    static int bit = 0;
    static unsigned char character = 0;
    static  pid_t pid;

    (void)context;
    if(pid != info->si_pid)
    {
        pid = info->si_pid;
        character = 0;
        bit = 0;
    }
    if (sig == SIGUSR1)
        character |= (1 << (7 - bit));

    bit++;

    if (bit == 8)
    {
        write(1, &character, 1);
        if (character == '\0')
            write(1, "\n", 1);
        bit = 0;
        character = 0;
    }

    kill(info->si_pid, SIGUSR1);
}

int main(void)
{
    struct sigaction sa;

    sa.sa_sigaction = handle_signal;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);

    printf("Server PID: %d\n", getpid());

    if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
    {
        perror("sigaction");
        return (1);
    }

    while (1)
        pause();
}
