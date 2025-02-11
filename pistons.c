/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pistons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 21:54:00 by cmassol           #+#    #+#             */
/*   Updated: 2025/02/11 17:45:14 by cmassol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	eater(t_philo *philo);
static void safe_mutex_all(t_philo *philo);
static int	eat_mutex_2(t_philo *philo);

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
		//safe_mutex(UNLOCK, &philo->philo_mutex);
		//print_status(philo, "is thinking", gettime(MILLISECOND));
		printer(gettime(MILLISECOND), philo, "is thinking");
		if (eater(philo))
			return (NULL);
		else
			safe_mutex_all(philo);
	}
	return (NULL);
}

static int	eater(t_philo *philo)
{
	if (!eat_mutex(philo))
	{
		if (!philo->died && !philo->table->philo_died)
		{
			//print_status(philo, "is sleeping", gettime(MILLISECOND));
			printer(gettime(MILLISECOND), philo, "is sleeping");
			ft_usleep(philo->time_sleep * 1000, philo->table);
		}
		else
		{
			//safe_mutex(UNLOCK, &philo->philo_mutex);
			return (1);
		}
	}
	else
	{
		//safe_mutex(UNLOCK, &philo->philo_mutex);
		//safe_mutex_all(philo);
		return (1);
	}
	return (0);
}

static void safe_mutex_all(t_philo *philo)
{
	safe_mutex(UNLOCK, &philo->philo_mutex);
	safe_mutex(UNLOCK, &philo->lfork->fork_mutex);
	safe_mutex(UNLOCK, &philo->rfork->fork_mutex);
}

int	eat_mutex(t_philo *philo)
{
	while (philo->died == 0 && philo->table->philo_died == 0)
	{
		if (safe_mutex(LOCK, &philo->lfork->fork_mutex) != 0)
		{
			return (1);
			//if (philo->died || philo->table->philo_died)
		}
		printer(gettime(MILLISECOND), philo, "has taken a fork");
		if (safe_mutex(LOCK, &philo->rfork->fork_mutex) != 0)
		{
			safe_mutex(UNLOCK, &philo->lfork->fork_mutex);
			return (1);
		}
		printer(gettime(MILLISECOND), philo, "has taken a fork");

		//safe_mutex(LOCK, &philo->philo_mutex);
/*		if (philo->died == 1 || philo->table->philo_died == 1)
		{
			safe_mutex(UNLOCK, &philo->philo_mutex);
			return (1);
		}
		else if (philo->table->nb_philo == 1)
		{
			philo->died = 1;
			safe_mutex(UNLOCK, &philo->philo_mutex);
			return (1);
		}*/
		break;
	}
	return (eat_mutex_2(philo));
}

static int	eat_mutex_2(t_philo *philo)
{	
	if ((philo->meals_eaten < philo->meals_max) || philo->meals_max == 0)
	{
		//print_status(philo, "is eating", gettime(MILLISECOND));
		printer(gettime(MILLISECOND), philo, "is eating");
		if (safe_mutex(LOCK, &philo->philo_mutex) != 0)
			return (1);
		philo->meals_eaten++;
		philo->last_meal_time = gettime(MILLISECOND);
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
