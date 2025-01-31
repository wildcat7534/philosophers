/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 06:25:48 by cmassol           #+#    #+#             */
/*   Updated: 2025/01/30 01:40:14 by cmassol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	safe_mutex(t_code_mtx code, t_mtx *mutex)
{
	if (code == INIT)
	{
		if (pthread_mutex_init(mutex, NULL) != 0)
			error("mutex init failed");
	}
	else if (code == LOCK)
	{
		if (pthread_mutex_lock(mutex) != 0)
			error("mutex lock failed");
	}
	else if (code == UNLOCK)
	{
		if (pthread_mutex_unlock(mutex) != 0)
			error("mutex unlock failed");
	}
	else if (code == DESTROY)
	{
		if (pthread_mutex_destroy(mutex) != 0)
			error("mutex destroy failed");
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
			error("thread creation failed");
			return (1);
		}
	}
	else if (code == JOIN)
	{
		if (pthread_join(philo->tid, NULL) != 0)
		{
			printf("%s ERROR : THREAD [%ld]%s JOIN failed\n", RED, philo->tid,  RESET);
			error("thread join failed");
			return (1);
		}
	}
	else if (code == DETACH)
	{
		if (pthread_detach(philo->tid) != 0)
		{
			printf("%s ERROR : THREAD [%ld]%s DETACH failed\n", RED, philo->tid,  RESET);
			error("thread detach failed");
			return (1);
		}
	}
	return (0);
}

void	safe_malloc(t_smalloc code, t_table *table)
{
	if (code == MALLOC_PHILOSOPHERS)
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
}
