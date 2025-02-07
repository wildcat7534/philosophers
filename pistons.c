/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pistons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 21:54:00 by cmassol           #+#    #+#             */
/*   Updated: 2025/02/07 12:59:27 by cmassol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*thd_rte(void *data)
{
	t_philo		*philo;
	philo = (t_philo *)data;

	safe_mutex(LOCK, &philo->philo_mutex);
	while (!philo->died && !philo->table->philo_died)
	{
		if (philo->meals_eaten >= philo->meals_max && philo->meals_max != 0)
			break;
		safe_mutex(UNLOCK, &philo->philo_mutex);
		if (!eat_mutex(philo))
		{
			if (!philo->died && !philo->table->philo_died)
			{
				print_status(philo, "is sleeping", gettime(MILLISECOND));
				ft_usleep(philo->time_sleep * 1000, philo->table);
			}
			else
				return (NULL);
		}
		else
			return (NULL);
		safe_mutex(UNLOCK, &philo->philo_mutex);
		print_status(philo, "is thinking", gettime(MILLISECOND));
	}
	safe_mutex(UNLOCK, &philo->philo_mutex);
	safe_mutex(UNLOCK, &philo->lfork->fork_mutex);
	safe_mutex(UNLOCK, &philo->rfork->fork_mutex);
	return (NULL);
}

int	eat_mutex(t_philo *philo)
{
	//safe_mutex(LOCK, &philo->philo_mutex);
	printf("Philo %d is trying to eat\n", philo->id);
	while (philo->died == 0 && philo->table->philo_died == 0)
	{
		if (safe_mutex(LOCK, &philo->lfork->fork_mutex) != 0)
		{
			if (philo->died || philo->table->philo_died)
			{
				//safe_mutex(UNLOCK, &philo->philo_mutex);
				return (1);
			}
			//continue;
		}
		if (philo->table->nb_philo == 1)
		{
			safe_mutex(UNLOCK, &philo->lfork->fork_mutex);
			//safe_mutex(UNLOCK, &philo->philo_mutex);
			return (1);
		}
		if (safe_mutex(LOCK, &philo->rfork->fork_mutex) != 0)
		{
			safe_mutex(UNLOCK, &philo->lfork->fork_mutex);
			//safe_mutex(UNLOCK, &philo->philo_mutex);
			return (1);
		}
		if (philo->died == 1 || philo->table->philo_died == 1)
		{
			safe_mutex(UNLOCK, &philo->lfork->fork_mutex);
			safe_mutex(UNLOCK, &philo->rfork->fork_mutex);
			//safe_mutex(UNLOCK, &philo->philo_mutex);
			return (1);
		}
		break;
	}
	if ((philo->meals_eaten < philo->meals_max) || philo->meals_max == 0)
	{
		print_status(philo, "is eating", gettime(MILLISECOND));
		philo->meals_eaten++;
		if (safe_mutex(LOCK, &philo->philo_mutex) != 0)
			return (1);
		philo->last_meal_time = gettime(MILLISECOND);
		printf("Philo %d is eating at %ld\n", philo->id, philo->last_meal_time - philo->table->t_start);
		safe_mutex(UNLOCK, &philo->philo_mutex);
		ft_usleep(philo->time_eat * 1000, philo->table);
	}
	else
	{
		safe_mutex(UNLOCK, &philo->lfork->fork_mutex);
		safe_mutex(UNLOCK, &philo->rfork->fork_mutex);
		//safe_mutex(UNLOCK, &philo->philo_mutex);
		return (1);
	}
	//safe_mutex(UNLOCK, &philo->philo_mutex);
	safe_mutex(UNLOCK, &philo->lfork->fork_mutex);
	safe_mutex(UNLOCK, &philo->rfork->fork_mutex);
	return (0);
}