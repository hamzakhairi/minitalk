#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

volatile int ack_received = 0;

void handle_ack(int sig)
{
    (void)sig;
    ack_received = 1;
}

void send_char(pid_t server_pid, char c)
{
    int bit;

    for (bit = 7; bit >= 0; bit--)
    {
        ack_received = 0;
        if ((c >> bit) & 1)
            kill(server_pid, SIGUSR1);
        else
            kill(server_pid, SIGUSR2);

        while (!ack_received)
            usleep(100);
    }
}

void send_message(pid_t server_pid, char *message)
{
    while (*message)
    {
        send_char(server_pid, *message);
        message++;
    }
    send_char(server_pid, '\0');
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("Usage: %s <server_pid> <message>\n", argv[0]);
        return (1);
    }

    pid_t server_pid = atoi(argv[1]);
    if (server_pid <= 0)
    {
        printf("Invalid PID\n");
        return (1);
    }

    struct sigaction sa;
    sa.sa_handler = handle_ack;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);

    send_message(server_pid, argv[2]);
    return (0);
}
