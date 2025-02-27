/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 14:33:49 by hkhairi           #+#    #+#             */
/*   Updated: 2025/01/02 21:29:59 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"  

void	handel_binary(int sig)
{
	static int	i = 0;
	static char	c[8];

	if (sig == SIGUSR1)
		c[i] = '1';
	else if (sig == SIGUSR2)
		c[i] = '0';
	i++;
	if (i == 8)
	{
		i = 0;
		convert_to_txt(c);
	}
}

int	main(void)
{
	ft_putnbr(getpid());
	write(1, "\n", 1);
	signal(SIGUSR1, handel_binary);
	signal(SIGUSR2, handel_binary);
	while (1)
		sleep(1);
	return (0);
}
