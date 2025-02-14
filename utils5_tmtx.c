/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5_tmyx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:54:12 by cmassol           #+#    #+#             */
/*   Updated: 2025/02/14 16:54:30 by cmassol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int mtx_table_maxmeals(t_table *table)
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

long mtx_table_tdie(t_table *table)
{
	long	t_die;
	safe_mutex(LOCK, &table->table_mutex);
	t_die = table->time_die;
	safe_mutex(UNLOCK, &table->table_mutex);
	return (t_die);
}
int mtx_table_teat(t_table *table)
{
	int	t_eat;
	safe_mutex(LOCK, &table->table_mutex);
	t_eat = table->time_eat;
	safe_mutex(UNLOCK, &table->table_mutex);
	return (t_eat);
}
