/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <mminet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:51:34 by mminet            #+#    #+#             */
/*   Updated: 2024/04/18 18:29:36 by mminet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philos
{
	unsigned int	nbr_philos;
	unsigned int	time_eat;
	unsigned int	time_sleep;
	unsigned int	time_die;
	int				nbr_meal;
	pthread_mutex_t	output;
	pthread_mutex_t	*fork;
}					t_philos;

typedef struct s_philo
{
	int				*dead;
	unsigned int	start;
	unsigned int	nbr_philos;
	unsigned int	time_eat;
	unsigned int	time_sleep;
	unsigned int	time_die;
	unsigned int	last_meal;
	int				nbr_meal;
	int				index;
	pthread_mutex_t	*output;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*fork_l;
}					t_philo;

void				put_nbr(long nbr);
unsigned long		to_milisecond(int second, int micro, int mili);
unsigned long		to_microsecond(int second, int micro, int mili);
void				create_philo(t_philo *philo);
void				ft_putstr(char *str);
int					ft_strlen(char *str);
int					ft_atoi(char *str);

#endif
