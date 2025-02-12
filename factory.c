/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 06:25:48 by cmassol           #+#    #+#             */
/*   Updated: 2025/02/12 01:08:30 by cmassol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	safe_mutex(t_code_mtx code, t_mtx *mutex)
{
	if (code == INIT)
	{
		if (pthread_mutex_init(mutex, NULL) != 0)
			return (error("mutex init failed"));
	}
	else if (code == LOCK)
	{
		if (pthread_mutex_lock(mutex) != 0)
			return (error("mutex lock failed"));
	}
	else if (code == UNLOCK)
	{
		if (pthread_mutex_unlock(mutex) != 0)
			return (error("mutex unlock failed"));
	}
	else if (code == DESTROY)
	{
		if (pthread_mutex_destroy(mutex) != 0)
			return (error("mutex destroy failed"));
	}
	return (0);
}

int	safe_thread(t_code_thread code, t_philo *philo,
		void *(*thd_rte)(void *))
{
	if (code == CREATE)
	{
		if (pthread_create(&philo->tid, NULL, thd_rte, philo) != 0)
		{
			printf("%s>ERROR : THREAD [%ld]%s CREATE failed\n", RED, philo->tid,  RESET);
			return (error("thread creation failed"));
		}
	}
	else if (code == JOIN)
	{
		if (pthread_join(philo->tid, NULL) != 0)
		{
			printf("%s ERROR : THREAD [%ld]%s JOIN failed\n", RED, philo->tid,  RESET);
			return (error("thread join failed"));
		}
	}
	else if (code == DETACH)
	{
		if (pthread_detach(philo->tid) != 0)
		{
			printf("%s ERROR : THREAD [%ld]%s DETACH failed\n", RED, philo->tid,  RESET);
			return (error("thread detach failed"));
		}
	}
	return (0);
}

t_table	*safe_malloc(t_smalloc code, t_table *table)
{
	if (code == MALLOC_TABLE)
	{
		table = malloc(sizeof(t_table));
		if (table == NULL)
			error("malloc table failed");
	}
	else if (code == MALLOC_PHILOSOPHERS)
	{
		table->philo = malloc(sizeof(t_philo) * table->nb_philo);
		if (table->philo == NULL)
			error("malloc Philo failed");
	}
	else if (code == MALLOC_FORKS)
	{
		table->forks = malloc(sizeof(t_forks) * table->nb_philo);
		if (table->forks == NULL)
			error("malloc forks failed");
	}
	return (table);
}
