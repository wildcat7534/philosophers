/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 06:35:32 by cmassol           #+#    #+#             */
/*   Updated: 2025/02/16 19:22:03 by cmassol          ###   ########.fr       */
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

long	time_micro(struct timeval start, struct timeval end)
{
	return ((end.tv_sec - start.tv_sec) * 1e6 + (end.tv_usec - start.tv_usec));
}

void	ft_usleep(long usec, t_table *table)
{
	long			elapsed;
	long			rem;
	struct timeval	start;
	struct timeval	stop;
	long			t_die;

	elapsed = 0;
	t_die = mtx_table_tdie(table);
	gettimeofday(&start, NULL);
	while (elapsed < usec)
	{
		gettimeofday(&stop, NULL);
		elapsed = time_micro(start, stop);
		rem = usec - elapsed;
		if (usec >= t_die || m_tsleep(table) >= t_die || m_teat(table) >= t_die)
		{
			//printf("%ld %d T died\n", gettime(MILLISECOND) - table->t_start, m_id(&table->philo[0]));
			//m_die_w(table);
			//table->philo_died = 1;
			usleep(t_die);
			all_stop_simulation(table);
			return ;
		}
		if (rem > 1000)
			usleep(rem / 2);
	}
}
