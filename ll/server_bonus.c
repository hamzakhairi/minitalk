
#include "minitalk.h"

void	handler(int sig, siginfo_t *siginfo, void *no)
{
	static int				i;
	static int				pid;
	static unsigned char	b;

	no = NULL;
	if (pid == 0 || pid != siginfo->si_pid)
	{
		pid = siginfo->si_pid;
		i = 0;
		b = 0;
	}
	if (sig == SIGUSR1)
		b |= (1 << i);
	i++;
	if (i == 8)
	{
		if (b != '\0')
			write(1, &b, 1);
		b = 0;
		i = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	put_str("Server PID = {%d}\n", getpid());
	sa.sa_sigaction = &handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
