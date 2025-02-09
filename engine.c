/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:19:41 by cmassol           #+#    #+#             */
/*   Updated: 2025/02/09 15:29:36 by cmassol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	start_simulation(t_table *table)
{
	int	i;

	i = -1;
	safe_mutex(INIT, &table->table_mutex);
	table->t_start = gettime(MILLISECOND);
	while (++i < table->nb_philo)
	{
		if (safe_thread(CREATE, &table->philo[i], thd_rte))
			return (1);
		ft_usleep(1000, table);
	}
	firewatch(table, table->t_start);
	i = -1;
	while (++i < table->nb_philo)
		safe_thread(JOIN, &table->philo[i], thd_rte);
	ft_free(table);
	return (0);
}
