/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <mminet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:12:51 by mminet            #+#    #+#             */
/*   Updated: 2024/04/20 00:26:43 by mminet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

unsigned long	ft_atoi(char *str)
{
	unsigned long	nbr;
	int				i;

	i = 0;
	nbr = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		nbr = (nbr * 10) + (str[i] - 48);
		i++;
	}
	return (nbr);
}
void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

void			put_nbr(long nbr)
{
	int c;
	if (nbr >= 10)
		put_nbr(nbr / 10);
	c = (nbr % 10) + 48; 
	write(1, &c, 1);
}

unsigned long	to_microsecond(unsigned long second, unsigned long micro, unsigned long mili)
{
	int res;
	res = second * 1e+6;
	res += mili * 1000;
	res += micro;
	return (res);
}

unsigned long	to_milisecond(unsigned long second, unsigned long micro, unsigned long mili)
{
	unsigned long res;
	res = second * 1000;
	res += mili;
	res += micro / 1000;
	return (res);
}
