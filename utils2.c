/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:51:38 by cmassol           #+#    #+#             */
/*   Updated: 2025/02/16 17:57:34 by cmassol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
		pthread_mutex_destroy(&table->philo[i].lfork->fork_mutex);
		pthread_mutex_destroy(&table->philo[i].philo_mutex);
	}
	pthread_mutex_destroy(&table->table_mutex);
	//free(table->printer->status);
	free(table->printer);
	free(table->philo);
	free(table->forks);
	free(table);
}

void	all_stop_simulation(t_table *table)
{
	int	i;
	int	nb_philo;

	nb_philo = mtx_tnb_philo(table);
	i = -1;
	while (++i < nb_philo)
	{
		mtx_stop_sim_write(&table->philo[i]);
	}
}

long	el_st(long time_start)
{
	return (gettime(MILLISECOND) - time_start);
}

int	all_eaten(t_table *table)
{
	int	i;
	int	max_meals;
	int	nb_philo;

	i = -1;
	nb_philo = mtx_tnb_philo(table);
	max_meals = mtx_table_maxmeals(table);
	while (++i < nb_philo)
	{
		if (mtx_meal_eat_philo(&table->philo[i]) < max_meals)
			return (0);
	}
	return (1);
}
