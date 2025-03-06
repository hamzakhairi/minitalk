/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 00:17:29 by hkhairi           #+#    #+#             */
/*   Updated: 2025/03/06 02:14:18 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static volatile sig_atomic_t	g_client_pid = 0;

void	handle_character(char character)
{
	if (character == '\0')
		kill(g_client_pid, SIGUSR1);
	else
		write(1, &character, 1);
}

void	send_signal()
{
	if (-1 == kill(g_client_pid, SIGUSR1))
	{
		fialde_programe("Error : kille faild !\n");
	}
}

void	handle_signal(int signum, siginfo_t *info, void *context)
{
	static int					bit = 0;
	static  unsigned char		character = 0;

	(void)context;
	if (g_client_pid == 0 || g_client_pid != info->si_pid)
	{
		g_client_pid = info->si_pid;
		bit = 0;
		character = 0;
	}
	character = character << 1;
    if (signum == SIGUSR1)
    {
        character = character | 1;
    }
	bit++;
	if (bit == 8)
	{
		handle_character(character);
		if (character == '\0')
			send_signal();
		bit = 0;
		character = 0;
		usleep(500);
	}
}

int	main(void)
{
	struct sigaction	sa;

	put_str("Server PID = ");
	ft_putnbr(getpid());
	put_str("\n");
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (-1 == sigaction(SIGUSR1, &sa, NULL))
		fialde_programe("Error : sigaction failde !\n");
	if (-1 == sigaction(SIGUSR2, &sa, NULL))
		fialde_programe("Error : sigaction failde !\n");
	while (1)
		pause();
	return (0);
}
