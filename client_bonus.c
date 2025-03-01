#include "minitalk.h"

volatile sig_atomic_t g_ack_received = 0;

void	ack_handler(int signum)
{
	(void)signum;
	g_ack_received = 1;
}

void	send_character(pid_t server_pid, char character)
{
	int i;

	i = 7;
	while (i >= 0)
	{
		g_ack_received = 0;
		if ((character >> i) & 1)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		while (!g_ack_received)
			pause();
		i--;
	}
}

void	send_message(pid_t server_pid, char *message)
{
	int	i;

	i = 0;
	while (message[i])
	{
		send_character(server_pid, message[i]);
		i++;
	}
	send_character(server_pid, '\0');
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;

	if (argc != 3 || argv[1][0] == '\0' || argv[2][0] == '\0')
	{
		put_str("Usage: ./client <server_pid> <message>\n");
		return (1);
	}
	signal(SIGUSR1, ack_handler);
	server_pid = ft_atoi(argv[1]);
	send_message(server_pid, argv[2]);
	return (0);
}
