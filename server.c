/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 00:07:38 by hkhairi           #+#    #+#             */
/*   Updated: 2025/03/03 14:47:46 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
	if (-1 == sigaction(SIGUSR1, &sa, NULL))
		fialde_programe("Error : sigaction failde !\n");
	if (-1 == sigaction(SIGUSR2, &sa, NULL))
		fialde_programe("Error : sigaction failde !\n");
	while (1)
		pause();
	return (0);
}
