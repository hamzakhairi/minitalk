/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 23:56:39 by hkhairi           #+#    #+#             */
/*   Updated: 2025/03/06 01:36:31 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static volatile sig_atomic_t	g_ack_received = 0;

void	ack_handler(int signum)
{
	(void)signum;
	g_ack_received = 1;
	printf("Message received completely.\n");
}

void	send_character(pid_t server_pid, char character)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		g_ack_received = 0;
		if ((character >> i) & 1)
		{
			if (kill(server_pid, SIGUSR1) == -1)
				fialde_programe("Error: kill failed!\n");
		}
		else
		{
			if (kill(server_pid, SIGUSR2) == -1)
				fialde_programe("Error: kill failed!\n");
		}
		usleep(600);
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
	while (!g_ack_received)
		pause();
}

int	main(int argc, char **argv)
{
	pid_t				server_pid;
	struct sigaction	sa;

	if (argc != 3 || argv[1][0] == '\0' || argv[2][0] == '\0')
	{
		put_str("Usage: ./client <server_pid> <message>\n");
		return (1);
	}
	sa.sa_handler = ack_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	server_pid = ft_atoi(argv[1]);
	send_message(server_pid, argv[2]);
	return (0);
}
