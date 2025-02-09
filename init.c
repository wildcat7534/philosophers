/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 23:44:18 by cmassol           #+#    #+#             */
/*   Updated: 2025/02/09 15:32:58 by cmassol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	initialisator(t_table *table);

t_table	*init_philosophers(int arc, char **argv)
{
	t_table		*table;

	table = NULL;
	table = safe_malloc(MALLOC_TABLE, table);
	table->nb_philo = ft_atoi(argv[1]);
	table->time_die = ft_atoi(argv[2]);
	table->time_eat = ft_atoi(argv[3]);
	table->time_sleep = ft_atoi(argv[4]);
	if (arc == 6)
		table->meals_max = ft_atoi(argv[5]);
	else
		table->meals_max = 0;
	safe_malloc(MALLOC_PHILOSOPHERS, table);
	safe_malloc(MALLOC_FORKS, table);
	safe_mutex(INIT, &table->table_mutex);
	table->philo_died = 0;
	table->t_start = gettime(MILLISECOND);
	initialisator(table);
	return (table);
}

static void	initialisator(t_table *table)
{
	t_philo		*philo;
	int			i;

	i = -1;
	while (++i < table->nb_philo)
	{
		philo = &table->philo[i];
		safe_mutex(INIT, &table->philo[i].philo_mutex);
		philo->id = i + 1;
		philo->time_die = table->time_die;
		philo->time_eat = table->time_eat;
		philo->time_sleep = table->time_sleep;
		philo->meals_max = table->meals_max;
		philo->meals_eaten = 0;
		philo->died = 0;
		philo->last_meal_time = gettime(MILLISECOND) - table->t_start;
		philo->lfork = &table->forks[i];
		philo->rfork = &table->forks[(i + 1) % table->nb_philo];
		safe_mutex(INIT, &philo->lfork->fork_mutex);
		philo->lfork->fork_id = i;
		philo->table = table;
	}
}
