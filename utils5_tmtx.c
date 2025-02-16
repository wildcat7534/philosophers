/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5_tmtx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:54:12 by cmassol           #+#    #+#             */
/*   Updated: 2025/02/16 20:21:20 by cmassol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	mtx_table_maxmeals(t_table *table)
{
	int	t_max_meals;

	safe_mutex(LOCK, &table->table_mutex);
	t_max_meals = table->meals_max;
	safe_mutex(UNLOCK, &table->table_mutex);
	return (t_max_meals);
}

int	mtx_tnb_philo(t_table *table)
{
	int	t_nb_philo;

	safe_mutex(LOCK, &table->table_mutex);
	t_nb_philo = table->nb_philo;
	safe_mutex(UNLOCK, &table->table_mutex);
	return (t_nb_philo);
}

long	mtx_table_tdie(t_table *table)
{
	long	t_die;

	safe_mutex(LOCK, &table->table_mutex);
	t_die = table->time_die;
	safe_mutex(UNLOCK, &table->table_mutex);
	return (t_die);
}

long	m_teat(t_table *table)
{
	int	t_eat;

	safe_mutex(LOCK, &table->table_mutex);
	t_eat = table->time_eat;
	safe_mutex(UNLOCK, &table->table_mutex);
	return (t_eat);
}

long	m_tsleep(t_table *table)
{
	int	t_sleep;

	safe_mutex(LOCK, &table->table_mutex);
	t_sleep = table->time_sleep;
	safe_mutex(UNLOCK, &table->table_mutex);
	return (t_sleep);
}

int	m_if_die_r(t_table *table)
{
	int	t_die;

	safe_mutex(LOCK, &table->table_mutex);
	t_die = table->philo_died;
	safe_mutex(UNLOCK, &table->table_mutex);
	return (t_die);
}

void m_die_w(t_table *table)
{
	safe_mutex(LOCK, &table->table_mutex);
	table->philo_died = 1;
	safe_mutex(UNLOCK, &table->table_mutex);
}

