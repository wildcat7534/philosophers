/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pistons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 21:54:00 by cmassol           #+#    #+#             */
/*   Updated: 2025/02/13 15:45:07 by cmassol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int 	eat_mutex(t_philo *philo, int id, long t_start);
static int	eat_mutex_2(t_philo *philo, int id, long t_start);

void	*thd_rte(void *data)
{
	t_philo		*philo;
	int			meal_max;
	int			id;
	long		t_start;
	
	philo = (t_philo *)data;
	id = mtx_read_id(philo);
	meal_max = mtx_p_max_meals(philo);
	t_start = mtx_p_t_start(philo);
	if (id % 2 == 0 )
		ft_usleep((philo->time_eat) * 1000);
	while (!mtx_stop_sim_read(philo))
	{
		if (meal_max != 0)
		{
			if (mtx_meal_eat_philo(philo) >= meal_max)
				break;
		}
		printer(gettime(MILLISECOND) - t_start, id, "is thinking");
		if (eater(philo, id, t_start) && mtx_stop_sim_read(philo))
		{
			///printf(mtx_stop_sim_read(philo) ? "true\n" : "false\n");
			//printf("philo %d end thread..\n", id);
			return (NULL);
		}
	}
	return (NULL);
}

int	eater(t_philo *philo, int id, long t_start)
{
	if (!eat_mutex(philo, id, t_start) && !mtx_stop_sim_read(philo))
	{
			printer(gettime(MILLISECOND) - t_start, id, "is sleeping");
			ft_usleep(philo->time_sleep * 1000);
	}
	else
		return (1);
	return (0);
}

static int	eat_mutex(t_philo *philo, int id, long t_start)
{
	if (!mtx_stop_sim_read(philo))
	{
		if (safe_mutex(LOCK, &philo->lfork->fork_mutex) != 0)
			return (1);
		printer(gettime(MILLISECOND) - t_start, id, "has taken a fork");
		//printf("mtx_nb_philo = %d\n", mtx_pnb_philo(philo));
		if (mtx_pnb_philo(philo) == 1)
		{
			safe_mutex(UNLOCK, &philo->lfork->fork_mutex);
			//printer(gettime(MILLISECOND) - t_start, id, "has give Lfork");
			//printf(mtx_stop_sim_read(philo) ? "true\n" : "false\n");
			ft_usleep(philo->time_die * 1000);
			//printf(mtx_stop_sim_read(philo) ? "true\n" : "false\n");
			return (1);
		}
		if (safe_mutex(LOCK, &philo->rfork->fork_mutex) != 0)
		{
			safe_mutex(UNLOCK, &philo->lfork->fork_mutex);
			return (1);
		}
		printer(gettime(MILLISECOND) - t_start, id, "has taken a fork");
		return(eat_mutex_2(philo, id, t_start));
	}
	return (1);
}

static int	eat_mutex_2(t_philo *philo, int id, long t_start)
{	
	if (!mtx_stop_sim_read(philo))
	{
		printer(gettime(MILLISECOND) - t_start, id, "is eating");
		safe_mutex(LOCK, &philo->philo_mutex);
		philo->meals_eaten++;
		safe_mutex(UNLOCK, &philo->philo_mutex);
		safe_mutex(LOCK, &philo->philo_mutex);
		philo->last_meal_time = gettime(MILLISECOND);
		safe_mutex(UNLOCK, &philo->philo_mutex);
		ft_usleep(philo->time_eat * 1000);
		safe_mutex(UNLOCK, &philo->rfork->fork_mutex);
		safe_mutex(UNLOCK, &philo->lfork->fork_mutex);
	}
	else
	{
		safe_mutex(UNLOCK, &philo->rfork->fork_mutex);
		safe_mutex(UNLOCK, &philo->lfork->fork_mutex);
		return (1);
	}
	return (0);
}
