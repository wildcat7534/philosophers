/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:19:41 by cmassol           #+#    #+#             */
/*   Updated: 2025/02/16 07:56:24 by cmassol          ###   ########.fr       */
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
		if (s_thd(CREATE, &table->philo[i], thd_rte) != 0)
			return (1);
	}
	firewatch(table, table->t_start);
	i = -1;
	while (++i < table->nb_philo)
		if (s_thd(JOIN, &table->philo[i], thd_rte) != 0)
			return (1);
	i = -1;
	ft_free(table);
	return (0);
}
