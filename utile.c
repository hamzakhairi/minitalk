/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:22:05 by hkhairi           #+#    #+#             */
/*   Updated: 2025/03/01 13:13:56 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int ft_atoi(char *str)
{
    int i;
    int res;

    i = 0;
    res = 0;
    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 32))
        i++;
    while ((str[i] >= '0' && str[i] <= '9'))
    {
        res = res * 10 + (str[i] - '0');
        i++;
    }
    return (res);
}

void put_char(char c)
{
    write(1, &c, 1);
}

void put_str(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        put_char(str[i]);
        i++;
    }
}

void	ft_putnbr(int n)
{
	if (n == -2147483648)
		put_str("-2147483648\n");
	else if (n < 0)
	{
		put_char('-');
		ft_putnbr(-1 * n);
	}
	else if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
	{
		ft_putchar(n + 48);
	}
}