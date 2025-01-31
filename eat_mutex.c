/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_mutex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 06:29:19 by cmassol           #+#    #+#             */
/*   Updated: 2025/01/30 10:54:40 by cmassol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	eat_mutex(t_philo *philo)
{
	while (philo->died == 0 && philo->table->philo_died == 0)
	{
		if (safe_mutex(LOCK, &philo->lfork->fork_mutex) != 0)
		{
			if (philo->died || philo->table->philo_died)
				return (1);
			continue;
		}
		if (philo->table->nb_philo == 1)
		{
			safe_mutex(UNLOCK, &philo->lfork->fork_mutex);
			return (1);
		}
		if (safe_mutex(LOCK, &philo->rfork->fork_mutex) != 0)
		{
			safe_mutex(UNLOCK, &philo->lfork->fork_mutex);
			return (1);
		}
		if (philo->died == 1 || philo->table->philo_died == 1)
		{
			safe_mutex(UNLOCK, &philo->lfork->fork_mutex);
			safe_mutex(UNLOCK, &philo->rfork->fork_mutex);
			return (1);
		}
		break;
	}
	if ((philo->meals_eaten < philo->meals_max) || philo->meals_max == 0)
	{
		print_status(philo, "is eating", gettime(MILLISECOND));
		safe_mutex(LOCK, &philo->philo_mutex);
		philo->meals_eaten++;
		philo->t_meal.tv_sec = gettime(MILLISECOND);
		safe_mutex(UNLOCK, &philo->philo_mutex);
		ft_usleep(philo->time_eat * 1000, philo->table);
	}
	else
	{
		safe_mutex(UNLOCK, &philo->lfork->fork_mutex);
		safe_mutex(UNLOCK, &philo->rfork->fork_mutex);
		return (1);
	}
	safe_mutex(UNLOCK, &philo->lfork->fork_mutex);
	safe_mutex(UNLOCK, &philo->rfork->fork_mutex);
	return (0);
}
