/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 00:17:29 by hkhairi           #+#    #+#             */
/*   Updated: 2025/03/10 13:55:07 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_signal(pid_t g_client_pid, unsigned char character)
{
	if (character != '\0')
		write(1, &character, 1);
	else
	{
		usleep(200);
		usleep(200);
		if (-1 == kill(g_client_pid, SIGUSR1))
		{
			failde_programe("Error : (server) kille faild !\n");
		}
	}
}

void	handle_signal(int sig, siginfo_t *siginfo, void *context)
{
	static int				index;
	static int				pid;
	static unsigned char	character;

	(void)context;
	if (pid != siginfo->si_pid)
	{
		pid = siginfo->si_pid;
		index = 0;
		character = 0;
	}
	if (siginfo->si_pid == 0)
		failde_programe("\nError: Received signal from unknown source.\n");
	if (sig == SIGUSR1)
		character |= (1 << index);
	index++;
	if (index == 8)
	{
		send_signal(pid, character);
		character = 0;
		index = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	put_str("Server PID = ");
	ft_putnbr(getpid());
	put_str("\n");
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_signal;
	sigemptyset(&sa.sa_mask);
	while (1)
	{
		if (-1 == sigaction(SIGUSR1, &sa, NULL))
			failde_programe("Error : sigaction failde !\n");
		if (-1 == sigaction(SIGUSR2, &sa, NULL))
			failde_programe("Error : sigaction failde !\n");
		pause();
	}
	return (0);
}
