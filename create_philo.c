/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <mminet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:33:13 by mminet            #+#    #+#             */
/*   Updated: 2024/04/21 22:23:38 by mminet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	my_time(unsigned long start)
{
	struct timeval tmp;
	gettimeofday(&tmp, NULL);
	return (to_milisecond(tmp.tv_sec, tmp.tv_usec, 0) - start);
}

int 	check_end(t_philo *philo)
{
	int res;

	res = 0;
	pthread_mutex_lock(philo->dead_mutex);
	if (*philo->dead)
		res = 1;
	pthread_mutex_unlock(philo->dead_mutex);
	return (res);
}

int		check_hungry(t_philo *philo)
{
	int res;

	res = 0;
	pthread_mutex_lock(&philo->eat);
	if (philo->nbr_meal != 0)
		res = 1;
	pthread_mutex_unlock(&philo->eat);
	return (res);
}

void	my_output(char *str, t_philo *philo)
{
	if (check_end(philo) || !check_hungry(philo))
		return;
	pthread_mutex_lock(philo->output);
	put_nbr(my_time(philo->start));
	write(1, " ", 1);
	put_nbr(philo->index);
	write(1, " ", 1);
	ft_putstr(str);
	write(1, "\n", 1);
	pthread_mutex_unlock(philo->output);
}

void	my_sleep(t_philo *philo, unsigned long value)
{
	unsigned long tmp;

	tmp = my_time(philo->start);
	while (my_time(philo->start) < (unsigned long)(tmp + value))
	{
		if (check_end(philo))
			break;
		usleep(50);
	}
}

void	eat(t_philo *philo)
{
		if (philo->index % 2 == 0)
		{
		 	pthread_mutex_lock(philo->fork_r);
		 	my_output("has taken a fork", philo);
		 	pthread_mutex_lock(philo->fork_l);
		 	my_output("has taken a fork", philo);
		}
		else
		{
			pthread_mutex_lock(philo->fork_l);
			my_output("has taken a fork", philo);
			pthread_mutex_lock(philo->fork_r);
			my_output("has taken a fork", philo);
		}
		pthread_mutex_lock(&philo->eat);
		philo->last_meal = my_time(philo->start);
		pthread_mutex_unlock(&philo->eat);
		my_output("is eating", philo);
		my_sleep(philo, philo->time_eat);
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(philo->fork_r);
		pthread_mutex_lock(&philo->eat);
		if (philo->nbr_meal > 0)
			philo->nbr_meal--;
		pthread_mutex_unlock(&philo->eat);
}

void	*start_philo(void	*arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->nbr_philos == 1)
	{
		my_output("has taken a fork", philo);
		return (NULL);
	}
	if (philo->index % 2 == 0)
		usleep(500);
	while (check_end(philo) == 0 && check_hungry(philo))
	{
		eat(philo);
		my_output("is sleeping", philo);
		my_sleep(philo, philo->time_sleep);
		my_output("is thinking", philo);
	}
	return (NULL);
}

int		check_dead(t_philo *philo, t_philos *philos)
{
	if (my_time(philos->start) - philo->last_meal > philos->time_die)
	{
		pthread_mutex_unlock(&philo->eat);
		my_output("is dead", philo);
		pthread_mutex_lock(&philos->dead_mutex);
		philos->dead = 1;
		pthread_mutex_unlock(&philos->dead_mutex);
		/*usleep(5000);
		put_nbr(my_time(philos->start));
		ft_putstr(" ");
		put_nbr(philo->index);
		ft_putstr(" is dead\n");*/
		return (1);
	}
	return (0);
}

void	*routine_end(void *arg)
{
	t_philos	*philos;
	unsigned int	i;
	int			check_nbr_eat;

	philos = (t_philos *)arg;
	while (1)
	{
		check_nbr_eat = 1;
		i = 0;
		while (i < philos->nbr_philos)
		{
			pthread_mutex_lock(&philos->philo[i].eat);
			if  (check_dead(&philos->philo[i], philos))
				return(NULL);
			if (philos->philo[i].nbr_meal != 0)
				check_nbr_eat = 0;
			pthread_mutex_unlock(&philos->philo[i].eat);
			i++;
		}
		if (check_nbr_eat)
		{
			pthread_mutex_lock(&philos->dead_mutex);
			philos->dead = 1;
			pthread_mutex_unlock(&philos->dead_mutex);
			return (NULL);
		}
		usleep(50);
	}
}

void	create_philo(t_philo *philo, t_philos *philos)
{
	unsigned int 	i;
	pthread_t		thread[philo[0].nbr_philos];
	pthread_t		routine_end_pth;

	i = 0;
	while (i < philo[0].nbr_philos)
	{
		pthread_create(&thread[i], NULL, start_philo, &philo[i]);
		i++;
	}
	i = 0;
	pthread_create(&routine_end_pth, NULL, routine_end, philos);
	while(i < philo[0].nbr_philos)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
	pthread_join(routine_end_pth, NULL);
}
