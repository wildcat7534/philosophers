/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6_tmtx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 01:22:49 by cmassol           #+#    #+#             */
/*   Updated: 2025/03/08 01:28:57 by cmassol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	m_if_die_r(t_table *table)
{
	int	t_die;

	safe_mutex(LOCK, &table->table_mutex);
	t_die = table->philo_died;
	safe_mutex(UNLOCK, &table->table_mutex);
	return (t_die);
}

void	m_die_w(t_table *table)
{
	safe_mutex(LOCK, &table->table_mutex);
	table->philo_died = 1;
	safe_mutex(UNLOCK, &table->table_mutex);
}

long	m_t_peat(t_philo *philo)
{
	long	t_eat;

	safe_mutex(LOCK, &philo->philo_mutex);
	t_eat = philo->time_eat;
	safe_mutex(UNLOCK, &philo->philo_mutex);
	return (t_eat);
}

long	m_tdie(t_philo *philo)
{
	long	t_die;

	safe_mutex(LOCK, &philo->philo_mutex);
	t_die = philo->time_die;
	safe_mutex(UNLOCK, &philo->philo_mutex);
	return (t_die);
}
