
#ifndef MINITALK_H
# define MINITALK_H

# include <stdarg.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>

int		ft_atoi(char *s);
char	*ft_strchr(const char *s, int c);
//put_str
int		put_str(const char *format, ...);
void	ft_putnbrbase(long long nbr, char *base, int *count);
int		ft_putstr(char *str);
int		ft_putchar(char c);
size_t	ft_strlen(const char *str);
void	ft_putnbrbaseunsigned(unsigned int nbr, char *base, int	*count);
void	ft_putnbr(int nb, int *count);
void	ft_putadr(unsigned long nbr, int *count);

#endif