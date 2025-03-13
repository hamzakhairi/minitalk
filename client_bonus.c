/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 23:56:39 by hkhairi           #+#    #+#             */
/*   Updated: 2025/03/10 14:03:42 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static volatile int	g_pid_received = 0;

void	ack_handler(int signum, siginfo_t *siginfo, void *context)
{
	(void)signum;
	(void)context;
	if (g_pid_received == siginfo->si_pid)
	{
		put_str("Message received completely.\n");
		exit(1);
	}
}

void	send_character(pid_t server_pid, char character)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		g_pid_received = server_pid;
		if (character & (1 << i))
		{
			if (kill(server_pid, SIGUSR1) == -1)
			{
				failde_programe("Error : (client 1) kill failde !\n");
			}
		}
		else
		{
			if (kill(server_pid, SIGUSR2) == -1)
			{
				failde_programe("Error : (client 2) kill failde !\n");
			}
		}
		usleep(200);
		usleep(200);
		i++;
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
	while (1)
		pause();
}

int	main(int argc, char **argv)
{
	pid_t				server_pid;
	struct sigaction	sa;

	if (argc != 3 || argv[1][0] == '\0')
	{
		put_str("Usage: ./client_bonus <server_pid> <message>\n");
		return (1);
	}
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ack_handler;
	sigemptyset(&sa.sa_mask);
	if (-1 == sigaction(SIGUSR1, &sa, NULL))
		failde_programe("Error : sigaction failde !\n");
	server_pid = ft_atoi(argv[1]);
	send_message(server_pid, argv[2]);
	return (0);
}
