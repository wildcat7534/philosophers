/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4_pmtx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:53:04 by cmassol           #+#    #+#             */
/*   Updated: 2025/02/16 22:03:09 by cmassol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	mtx_last_meal_time(t_philo *philo)
{
	long	last_meal_time;

	safe_mutex(LOCK, &philo->philo_mutex);
	last_meal_time = philo->last_meal_time;
	safe_mutex(UNLOCK, &philo->philo_mutex);
	return (last_meal_time);
}

int	mtx_p_max_meals(t_philo *philo)
{
	int	p_max_meals;

	safe_mutex(LOCK, &philo->philo_mutex);
	p_max_meals = philo->meals_max;
	safe_mutex(UNLOCK, &philo->philo_mutex);
	return (p_max_meals);
}

int	mtx_pnb_philo(t_philo *philo)
{
	int	p_nb_philo;

	safe_mutex(LOCK, &philo->philo_mutex);
	p_nb_philo = philo->nb_philo;
	safe_mutex(UNLOCK, &philo->philo_mutex);
	return (p_nb_philo);
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
