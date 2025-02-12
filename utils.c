/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 00:37:51 by cmassol           #+#    #+#             */
/*   Updated: 2025/02/12 01:20:35 by cmassol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	nb;

	i = 0;
	nb = 0;
	if (!str)
		return (0);
	if (ft_strlen(str) > 11)
		return (-1);
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		return (-1);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	check_argv_positivity(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) < 1)
			return (1);
		i++;
	}
	return (0);
}

void	ft_free(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nb_philo)
	{
		//ft_usleep(10000, table);
		pthread_mutex_destroy(&table->philo[i].lfork->fork_mutex);
		pthread_mutex_destroy(&table->philo[i].philo_mutex);
	}
	pthread_mutex_destroy(&table->table_mutex);
	free(table->philo);
	free(table->forks);
	free(table);
}

int mtx_died(t_philo *philo)
{
	int	p_died;
	safe_mutex(LOCK, &philo->philo_mutex);
	p_died = philo->died;
	safe_mutex(UNLOCK, &philo->philo_mutex);
	return (p_died);
}

int mtx_table_died(t_philo *philo)
{
	int	t_died;
	safe_mutex(LOCK, &philo->philo_mutex);
	t_died = philo->table->philo_died;
	safe_mutex(UNLOCK, &philo->philo_mutex);
	return (t_died);
}

int mtx_table_maxmeals(t_philo *philo)
{
	int	t_maxmeals;
	safe_mutex(LOCK, &philo->philo_mutex);
	t_maxmeals = philo->table->meals_max;
	safe_mutex(UNLOCK, &philo->philo_mutex);
	return (t_maxmeals);
}
int	mtx_nb_philo(t_philo *philo)
{
	int	nb_philo;
	safe_mutex(LOCK, &philo->philo_mutex);
	nb_philo = philo->table->nb_philo;
	safe_mutex(UNLOCK, &philo->philo_mutex);
	return (nb_philo);
}
long mtx_table_tdie(t_philo *philo)
{
	int	t_die;
	safe_mutex(LOCK, &philo->philo_mutex);
	t_die = philo->table->time_die;
	safe_mutex(UNLOCK, &philo->philo_mutex);
	return (t_die);
}

int mtx_meal_eat_philo(t_philo *philo)
{
	int	meal_eat;
	safe_mutex(LOCK, &philo->philo_mutex);
	meal_eat = philo->meals_eaten;
	safe_mutex(UNLOCK, &philo->philo_mutex);
	return (meal_eat);
}
