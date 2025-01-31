/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 23:44:18 by cmassol           #+#    #+#             */
/*   Updated: 2025/01/30 10:21:09 by cmassol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philosophers(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	safe_malloc(MALLOC_PHILOSOPHERS, table);
	safe_malloc(MALLOC_FORKS, table);
	safe_mutex(INIT, &table->table_mutex);
	table->philo_died = 0;
	table->t_start = gettime(MILLISECOND);
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
		philo->lfork = &table->forks[i];
		philo->rfork = &table->forks[(i + 1) % table->nb_philo];
		safe_mutex(INIT, &philo->lfork->fork_mutex);
		//printf("pthread init &philo[%d]->lfork\n", i);
		philo->lfork->fork_id = i;
		//philo->next = &table->philo[(i + 1) % table->nb_philo];
		philo->table = table;
	}
	// print all arg
printf("nb_philo: %d\ntime_die:%d\ntime_eat:%d\ntime_sleep:%d\nnb_meals_max:%d\n", 
	table->nb_philo,philo->time_die,philo->time_eat,philo->time_sleep,table->meals_max);
}
