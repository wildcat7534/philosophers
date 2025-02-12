/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 06:35:32 by cmassol           #+#    #+#             */
/*   Updated: 2025/02/12 21:49:52 by cmassol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	gettime(t_time_val time_val)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		error("gettimeofday failed");
	if (time_val == SECOND)
		return (time.tv_sec + (time.tv_usec / 1e6));
	else if (time_val == MILLISECOND)
		return (time.tv_sec * 1e3 + time.tv_usec / 1e3);
	else if (time_val == MICROSECOND)
		return (time.tv_sec * 1e6 + time.tv_usec);
	else
		error("Invalid time value");
	return (0);
}

long	get_elapsed_time_microseconds(struct timeval start, struct timeval end)
{
	return (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_usec
		- start.tv_usec);
}

void	ft_usleep(long usec)
{
	long			elapsed;
	long			rem;
	struct timeval	start;
	struct timeval	stop;
	
	elapsed = 0;
	gettimeofday(&start, NULL);
	while (elapsed < usec)
	{
		gettimeofday(&stop, NULL);
		elapsed = get_elapsed_time_microseconds(start, stop);
		rem = usec - elapsed;
		if (rem > 100)
			usleep(rem / 2);
/* 		if (elapsed / 1e3 >= mtx_table_tdie(table->philo) * 2)
		{
			safe_mutex(LOCK, &table->table_mutex);
			printf("TIME UP !!!(%ld) Philo %d died\n", elapsed, table->philo->id);
			table->philo_died = 1;
			safe_mutex(UNLOCK, &table->table_mutex);
			return ;
		} */
	}
}
