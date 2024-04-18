/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <mminet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:54:38 by mminet            #+#    #+#             */
/*   Updated: 2024/04/18 18:31:03 by mminet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	check_num(char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (av[i])
	{
		if (av[i][0] == '+')
			j++;
		while (av[i][j])
		{
			if (av[i][j] > '9' || av[i][j] < '0')
				return (0);
			j++;
		}
		i++;
		j = 0;
	}
	return (1);
}

int	parse(int ac, char **av, t_philos *philos)
{
	if (!check_num(av))
		return (0);
	philos->nbr_meal = -1;
	philos->nbr_philos = ft_atoi(av[1]);
	philos->time_die = ft_atoi(av[2]);
	philos->time_eat = ft_atoi(av[3]);
	philos->time_sleep = ft_atoi(av[4]);
	if (ac == 6)
		philos->nbr_meal = ft_atoi(av[5]);
	if (philos->nbr_philos < 1)
		return (0);
	philos->fork = malloc(sizeof(pthread_mutex_t) * philos->nbr_philos);
	return (1);
}

int	usage(void)
{
	ft_putstr("Error Usage\n");
	ft_putstr("number_of_philosophers ");
	ft_putstr("time_to_die time_to_eat ");
	ft_putstr("time_to_sleep ");
	ft_putstr("[number_of_times_each_philosopher_must_eat]\n");
	return (1);
}

void	cpy_philos(t_philos *philos)
{
	t_philo			*philo;
	struct timeval	start;
	unsigned int	i;
	int 			dead;

	i = 0;
	dead = 0;
	philo = malloc(sizeof(t_philo) * philos->nbr_philos);
	philo[0].fork_l = &philos->fork[philos->nbr_philos - 1];
	gettimeofday(&start, NULL);
	while (i < philos->nbr_philos)
	{
		if (i != 0)
			philo[i].fork_l = &philos->fork[i - 1];
		philo[i].start = to_milisecond(start.tv_sec, start.tv_usec, 0);
		philo[i].fork_r = &philos->fork[i];
		philo[i].output = &philos->output;
		philo[i].nbr_meal = philos->nbr_meal;
		philo[i].nbr_philos = philos->nbr_philos;
		philo[i].time_die = philos->time_die;
		philo[i].time_eat = philos->time_eat;
		philo[i].time_sleep = philos->time_sleep;
		philo[i].last_meal = philo[i].start;
		philo[i].index = i + 1;
		philo[i].dead = &dead;
		i++;
	}
	create_philo(philo);
}

int	main(int ac, char **av)
{
	t_philos		philos;
	unsigned int	i;

	if (ac < 5 || ac > 6 || !parse(ac, av, &philos))
		return (usage());
	i = 0;
	while (i < philos.nbr_philos)
	{
		pthread_mutex_init(&philos.fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&philos.output, NULL);
	cpy_philos(&philos);
}
