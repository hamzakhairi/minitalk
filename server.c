#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void handle_signal(int sig, siginfo_t *siginfo, void *context)
{
    static int				index;
	static int				pid;
	static unsigned char	character;

    (void)context;
	if (pid == 0 || pid != siginfo->si_pid)
	{
		pid = siginfo->si_pid;
		index = 0;
		character = 0;
	}
	if (sig == SIGUSR1)
		character |= (1 << index);
	index++;
	if (index == 8)
	{
		if (character != '\0')
			write(1, &character, 1);
		character = 0;
		index = 0;
	}
}

int main(void)
{
	struct sigaction	sa;

	put_str("Server PID = {%d}\n", getpid());
	sa.sa_sigaction = &handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
