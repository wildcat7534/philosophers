/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pistons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 21:54:00 by cmassol           #+#    #+#             */
/*   Updated: 2025/03/08 01:10:19 by cmassol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	eater(t_philo *philo, int id, long t_start);
static int	eat_mutex(t_philo *philo, int id, long t_start);
static int	eat_mutex_2(t_philo *philo, int id, long t_start);

void	*thd_rte(void *data)
{
	t_philo		*philo;
	int			meal_max;
	int			id;
	long		t_start;

	philo = (t_philo *)data;
	id = m_id(philo);
	meal_max = mtx_p_max_meals(philo);
	t_start = mtx_p_t_start(philo);
	if (id % 2 == 0)
		ft_usleep(m_t_peat(philo), philo->table);
	while (!m_stop_r(philo))
	{
		if (meal_max != 0)
		{
			if (mtx_meal_eat_philo(philo) >= meal_max)
				break ;
		}
		fprinter(t_start, id, "is thinking", philo->table);
		if (eater(philo, id, t_start) || m_stop_r(philo))
			return (NULL);
	}
	return (NULL);
}

static int	eater(t_philo *philo, int id, long t_start)
{
	if (!eat_mutex(philo, id, t_start) && !m_stop_r(philo))
	{
		fprinter(t_start, id, "is sleeping", philo->table);
		ft_usleep(philo->time_sleep, philo->table);
	}
	else
		return (1);
	return (0);
}

static int	eat_mutex(t_philo *philo, int id, long t_start)
{
	if (!m_stop_r(philo))
	{
		if (safe_mutex(LOCK, &philo->lfork->fork_mutex) != 0)
			return (1);
		fprinter(t_start, id, "has taken a fork", philo->table);
		if (mtx_pnb_philo(philo) == 1)
		{
			safe_mutex(UNLOCK, &philo->rfork->fork_mutex);
			ft_usleep(philo->time_die, philo->table);
			return (1);
		}
		if (m_stop_r(philo))
		{
			safe_mutex(UNLOCK, &philo->lfork->fork_mutex);
			return (1);
		}
		if (safe_mutex(LOCK, &philo->rfork->fork_mutex) != 0)
		{
			safe_mutex(UNLOCK, &philo->lfork->fork_mutex);
			return (1);
		}
		fprinter(t_start, id, "has taken a fork", philo->table);
		return (eat_mutex_2(philo, id, t_start));
	}
	return (1);
}

static int	eat_mutex_2(t_philo *philo, int id, long t_start)
{
	if (!m_stop_r(philo))
	{
		fprinter(t_start, id, "is eating", philo->table);
		safe_mutex(LOCK, &philo->philo_mutex);
		philo->meals_eaten++;
		safe_mutex(UNLOCK, &philo->philo_mutex);
		safe_mutex(LOCK, &philo->philo_mutex);
		philo->last_meal_time = gettime(MILLISECOND);
		safe_mutex(UNLOCK, &philo->philo_mutex);
		ft_usleep(philo->time_eat, philo->table);
		safe_mutex(UNLOCK, &philo->lfork->fork_mutex);
		safe_mutex(UNLOCK, &philo->rfork->fork_mutex);
	}
	else
	{
		safe_mutex(UNLOCK, &philo->lfork->fork_mutex);
		safe_mutex(UNLOCK, &philo->rfork->fork_mutex);
		return (1);
	}
	return (0);
}
