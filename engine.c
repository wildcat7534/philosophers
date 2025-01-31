/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:19:41 by cmassol           #+#    #+#             */
/*   Updated: 2025/01/30 11:38:41 by cmassol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	start_simulation(t_table *table)
{
	int		i;

	i = -1;
	safe_mutex(INIT, &table->table_mutex);
	table->t_start = gettime(MILLISECOND);
	while (++i < table->nb_philo)
	{
		if (safe_thread(CREATE, &table->philo[i], thd_rte))
			return (1);
		table->philo[i].t_meal.tv_sec = gettime(MILLISECOND) - table->t_start;
		ft_usleep(100, table);
		//printf("start simulation : Philo %d last meal time %ld\n", table->philo[i].id, table->philo[i].last_meal_time.tv_sec);
	}
	firewatch(table, table->t_start);
	//printf("start THE END at %ld\n", gettime(MILLISECOND) - table->time_start);
	i = -1;
	while (++i < table->nb_philo)
	{
		safe_thread(JOIN, &table->philo[i], thd_rte);
		//printf("Thread %d joined tid : %lu 🫱🏼‍🫲🏻\n", i+1, table->philo[i].tid);
	}
	//printf("end of simulation at %ld (time elapsed : %ld)\n", gettime(MILLISECOND), (gettime(MILLISECOND) - table->time_start));
	safe_mutex(UNLOCK, &table->table_mutex);
	return (0);
}
