/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:19:41 by cmassol           #+#    #+#             */
/*   Updated: 2025/02/12 22:23:51 by cmassol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	start_simulation(t_table *table)
{
	int	i;

	i = -1;
	table->t_start = gettime(MILLISECOND);
	while (++i < table->nb_philo)
	{
		if (mtx_read_id(&table->philo[i]) % 2 == 0)
			ft_usleep(table->time_eat * 1000);
		if (safe_thread(CREATE, &table->philo[i], thd_rte) != 0)
			return (1);
		//ft_usleep(420);
	}
	firewatch(table, table->t_start);
	i = -1;
	while (++i < table->nb_philo)
		if (safe_thread(JOIN, &table->philo[i], thd_rte) != 0)
			return (1);
	i = -1;
/* 	while (++i < table->nb_philo)
		if (safe_thread(DETACH, &table->philo[i], thd_rte) != 0)
			return (1); */
	ft_free(table);
	return (0);
}
