/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <mminet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:33:13 by mminet            #+#    #+#             */
/*   Updated: 2024/04/18 18:44:42 by mminet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	my_time(int start)
{
	struct timeval tmp;
	gettimeofday(&tmp, NULL);
	return (to_milisecond(tmp.tv_sec, tmp.tv_usec, 0) - start);
}

void	my_output(char *str, t_philo *philo)
{
	pthread_mutex_lock(philo->output);
	put_nbr(my_time(philo->start));
	write(1, " ", 1);
	put_nbr(philo->index);
	write(1, " ", 1);
	ft_putstr(str);
	write(1, "\n", 1);
	pthread_mutex_unlock(philo->output);
}

void	*start_philo(void	*arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(philo->fork_l);
		if (my_time(philo->last_meal) <= philo->time_die && !*philo->dead)
			break;
		my_output("has taken a fork", philo);
		pthread_mutex_lock(philo->fork_r);
		if (my_time(philo->last_meal) <= philo->time_die && !*philo->dead)
			break;
		my_output("has taken a fork", philo);
		philo->last_meal = my_time(philo->start);
		if (my_time(philo->last_meal) <= philo->time_die && !*philo->dead)
			break;
		my_output("is eating", philo);
		usleep(to_microsecond(0, 0, philo->time_eat));
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(philo->fork_r);
		if (my_time(philo->last_meal) > philo->time_die || *philo->dead)
			break;
		my_output("is sleeping", philo);
		usleep(to_microsecond(0, 0, philo->time_sleep));
		if (my_time(philo->last_meal) > philo->time_die || *philo->dead)
			break;
		my_output("is thinking", philo);
	}
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
	if (!*philo->dead == 0)
		my_output("is died", philo);
	*philo->dead = 1;
	return (NULL);
}

void	create_philo(t_philo *philo)
{
	unsigned int 	i;
	pthread_t		thread[philo[0].nbr_philos];

	i = 0;
	while (i < philo[0].nbr_philos)
	{
		pthread_create(&thread[i], NULL, start_philo, &philo[i]);
		usleep (to_microsecond(0, 5, 0));
		i++;
	}
	i = 0;
	while (i < philo[0].nbr_philos)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
}
