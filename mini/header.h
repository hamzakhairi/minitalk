/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 14:33:45 by hkhairi           #+#    #+#             */
/*   Updated: 2025/01/01 19:51:13 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <limits.h>
# include <stdlib.h>

void		ft_putchar(int c);
void		ft_putnbr(int num);
int		ft_atoi(char *str);
void		convert_to_binary(char *s, int pidserv);
void		convert_to_txt(char *s);

#endif
