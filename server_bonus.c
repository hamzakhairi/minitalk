#include "minitalk.h"

volatile sig_atomic_t g_client_pid = 0;

void	handle_signal(int signum, siginfo_t *info, void *context)
{
	static int		bit = 0;
	static char		character = 0;

	(void)context;
	if (g_client_pid == 0)
		g_client_pid = info->si_pid;
	character |= (signum == SIGUSR1);
	bit++;
	if (bit == 8)
	{
		if (character == '\0')
			put_str("\nMessage received completely.\n");
		else
			write(1, &character, 1);
		bit = 0;
		character = 0;
		usleep(500);
		kill(g_client_pid, SIGUSR1);
	}
	else
		character <<= 1;
}

int	main(void)
{
	struct sigaction sa;

	put_str("Server PID: %d\n", getpid());
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
