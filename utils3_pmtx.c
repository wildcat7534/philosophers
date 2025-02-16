/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_pmtx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:52:22 by cmassol           #+#    #+#             */
/*   Updated: 2025/02/16 08:13:41 by cmassol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned int	m_id(t_philo *philo)
{
	unsigned int	id;

	safe_mutex(LOCK, &philo->philo_mutex);
	id = philo->id;
	safe_mutex(UNLOCK, &philo->philo_mutex);
	return (id);
}

long	mtx_p_t_start(t_philo *philo)
{
	long	t_start;

	safe_mutex(LOCK, &philo->philo_mutex);
	t_start = philo->t_start;
	safe_mutex(UNLOCK, &philo->philo_mutex);
	return (t_start);
}

int	m_stop_r(t_philo *philo)
{
	int	stop_sim;

	safe_mutex(LOCK, &philo->philo_mutex);
	stop_sim = philo->stop_simulation;
	safe_mutex(UNLOCK, &philo->philo_mutex);
	return (stop_sim);
}

void	mtx_stop_sim_write(t_philo *philo)
{
	safe_mutex(LOCK, &philo->philo_mutex);
	philo->stop_simulation = 1;
	safe_mutex(UNLOCK, &philo->philo_mutex);
}

int	mtx_meal_eat_philo(t_philo *philo)
{
	int	meal_eat;

	safe_mutex(LOCK, &philo->philo_mutex);
	meal_eat = philo->meals_eaten;
	safe_mutex(UNLOCK, &philo->philo_mutex);
	return (meal_eat);
}
