/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:19:41 by cmassol           #+#    #+#             */
/*   Updated: 2025/02/13 15:25:42 by cmassol          ###   ########.fr       */
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
