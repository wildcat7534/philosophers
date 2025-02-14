/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:51:38 by cmassol           #+#    #+#             */
/*   Updated: 2025/02/14 16:52:13 by cmassol          ###   ########.fr       */
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
		//ft_usleep(10000, table);
		pthread_mutex_destroy(&table->philo[i].lfork->fork_mutex);
		pthread_mutex_destroy(&table->philo[i].philo_mutex);
	}
	pthread_mutex_destroy(&table->table_mutex);
	free(table->philo);
	free(table->forks);
	free(table);
}
