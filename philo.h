/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <mminet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:51:34 by mminet            #+#    #+#             */
/*   Updated: 2024/04/21 17:39:30 by mminet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>

typedef struct s_philo
{
	int				*dead;
	unsigned long	start;
	unsigned int	nbr_philos;
	unsigned long	time_eat;
	unsigned long	time_sleep;
	unsigned long	time_die;
	unsigned long	last_meal;
	int				nbr_meal;
	int				index;
	pthread_mutex_t *dead_mutex;
	pthread_mutex_t	*output;
	pthread_mutex_t	eat;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*fork_l;
}					t_philo;

typedef struct s_philos
{
	int				dead;
	unsigned int	nbr_philos;
	unsigned long	time_eat;
	unsigned long	time_sleep;
	unsigned long	time_die;
	int				nbr_meal;
	unsigned long	start;
	t_philo			*philo;
	pthread_mutex_t	output;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t eat;
	pthread_mutex_t	*fork;
}					t_philos;

void				put_nbr(long nbr);
unsigned long		to_milisecond(unsigned long second, unsigned long micro, unsigned long mili);
unsigned long		to_microsecond(unsigned long second, unsigned long micro, unsigned long mili);
void				create_philo(t_philo *philo, t_philos *philos);
void				ft_putstr(char *str);
int					ft_strlen(char *str);
unsigned long		ft_atoi(char *str);

#endif
