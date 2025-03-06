/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 00:17:29 by hkhairi           #+#    #+#             */
/*   Updated: 2025/03/06 20:16:20 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_signal(pid_t g_client_pid)
{
	if (usleep(600) == -1)
		failde_programe("Error : usleep failde !\n");
	if (-1 == kill(g_client_pid, SIGUSR1))
	{
		failde_programe("Error : kille faild !\n");
	}
}

void	handle_signal(int sig, siginfo_t *siginfo, void *context)
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
		else
			send_signal(pid);
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
	sa.sa_sigaction = &handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (-1 == sigaction(SIGUSR1, &sa, NULL))
		failde_programe("Error : sigaction failde !\n");
	if (-1 == sigaction(SIGUSR2, &sa, NULL))
		failde_programe("Error : sigaction failde !\n");
	while (1)
		pause();
	return (0);
}
