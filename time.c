/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 06:35:32 by cmassol           #+#    #+#             */
/*   Updated: 2025/02/07 19:30:41 by cmassol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
int	ft_times_up(int time)
{
	static struct timeval	start;
	struct timeval			now;
	long					elapsed;

	if (start.tv_sec == 0)
		gettimeofday(&start, NULL);
	gettimeofday(&now, NULL);
	elapsed = (now.tv_sec - start.tv_sec) * 1000.0;
	elapsed += (now.tv_usec - start.tv_usec) / 1000.0;
	if (elapsed >= time)
		return (1);
	return (0);
}

long	gettime(t_time_val time_val)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
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
	return (end.tv_sec - start.tv_sec) * 1000000L + (end.tv_usec
		- start.tv_usec);
}

void	ft_usleep(long usec, t_table *table)
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
		if (rem > 1000)
			usleep(rem / 2);
		safe_mutex(LOCK, &table->table_mutex);
		if (elapsed / 1e3 >= table->time_die && table->philo->died == 0)
		{
			printf("TIME UP !!!(%ld) Philo %d died\n", elapsed, table->philo->id);
			table->philo->died = 1;
			table->philo->table->philo_died = 1;
			safe_mutex(UNLOCK, &table->table_mutex);
			return ;
		}
		safe_mutex(UNLOCK, &table->table_mutex);
	}
}
