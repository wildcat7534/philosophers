/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pistons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 21:54:00 by cmassol           #+#    #+#             */
/*   Updated: 2025/02/12 01:14:15 by cmassol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	eater(t_philo *philo);
static int	eat_mutex_2(t_philo *philo);

void	*thd_rte(void *data)
{
	t_philo		*philo;
	
	philo = (t_philo *)data;
	while (!mtx_died(philo) && !mtx_table_died(philo))
	{
		if (philo->meals_eaten >= philo->meals_max && philo->meals_max != 0)
			break;
		printer(gettime(MILLISECOND), philo, "is thinking");

/*		if (philo->table->nb_philo % 2 == 0)
			ft_usleep(philo->time_eat * 1000, philo->table);*/
		if (eater(philo))
			return (NULL);
	}
	return (NULL);
}

static int	eater(t_philo *philo)
{
	if (!eat_mutex(philo))
	{
		if (!!mtx_died(philo) && !mtx_table_died(philo))
		{
			printer(gettime(MILLISECOND), philo, "is sleeping");
			ft_usleep(philo->time_sleep * 1000, philo->table);
		}
		else
			return (1);
	}
	else
		return (1);
	return (0);
}

int	eat_mutex(t_philo *philo)
{
	while (!mtx_died(philo) && ! mtx_table_died(philo))
	{
		if (safe_mutex(LOCK, &philo->lfork->fork_mutex) != 0)
			return (1);
		printer(gettime(MILLISECOND), philo, "has taken a fork");
		if (mtx_died(philo) || mtx_table_died(philo))
		{
			safe_mutex(UNLOCK, &philo->lfork->fork_mutex);
			return (1);
		}
		if (safe_mutex(LOCK, &philo->rfork->fork_mutex) != 0)
		{
			safe_mutex(UNLOCK, &philo->lfork->fork_mutex);
			return (1);
		}
		printer(gettime(MILLISECOND), philo, "has taken a fork");
		if (mtx_died(philo) || mtx_table_died(philo))
		{
			safe_mutex(UNLOCK, &philo->lfork->fork_mutex);
			safe_mutex(UNLOCK, &philo->rfork->fork_mutex);
			return (1);
		}
		else if (mtx_nb_philo(philo) == 1)
		{
			//philo->died = 1;
			safe_mutex(UNLOCK, &philo->lfork->fork_mutex);
			safe_mutex(UNLOCK, &philo->rfork->fork_mutex);
			return (1);
		}
		break;
	}
	return (eat_mutex_2(philo));
}

static int	eat_mutex_2(t_philo *philo)
{	
	if ((mtx_meal_eat_philo(philo) < mtx_table_maxmeals(philo)) || mtx_table_maxmeals(philo) == 0)
	{
		printer(gettime(MILLISECOND), philo, "is eating");
		safe_mutex(LOCK, &philo->philo_mutex);
		philo->meals_eaten++;
		safe_mutex(UNLOCK, &philo->philo_mutex);
		ft_usleep(100, philo->table);
		safe_mutex(LOCK, &philo->philo_mutex);
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
