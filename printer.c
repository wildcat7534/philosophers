/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:34:35 by cmassol           #+#    #+#             */
/*   Updated: 2025/03/08 09:50:59 by cmassol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	fprinter_died(long time, int id, char *status, t_table *table);
static void	fprinter_alive(long time, int id, char *status, t_table *table);

int	error(char *msg)
{
	printf("[%sError: %s%s]\n", RED, msg, RT);
	return (1);
}

void	fprinter(long time, int id, char *status, t_table *table)
{
	int		stop_sim;
	int		philo_died;

	safe_mutex(LOCK, &table->table_mutex);
	stop_sim = table->stop_simulation;
	philo_died = table->philo_died;
	safe_mutex(UNLOCK, &table->table_mutex);
	if (ft_strcmp(status, "died") == 0)
		fprinter_died(time, id, status, table);
	else if (philo_died == 0 && stop_sim == 0)
		fprinter_alive(time, id, status, table);
}

static void	fprinter_died(long time, int id, char *status, t_table *table)
{
	long	timestamp;

	timestamp = gettime(MILLISECOND);
	m_die_w(table);
	all_stop_simulation(table);
	safe_mutex(LOCK, &table->printer->p_mutex);
	printf("%ld %d %s\n", timestamp - time, id, status);
	safe_mutex(UNLOCK, &table->printer->p_mutex);
}

static void	fprinter_alive(long time, int id, char *status, t_table *table)
{
	int	stop_sim;
	int	philo_died;

	safe_mutex(LOCK, &table->table_mutex);
	stop_sim = table->stop_simulation;
	philo_died = table->philo_died;
	safe_mutex(UNLOCK, &table->table_mutex);
	safe_mutex(LOCK, &table->printer->p_mutex);
	if (philo_died == 0 && stop_sim == 0)
		printf("%ld %d %s\n", gettime(MILLISECOND) - time, id, status);
	safe_mutex(UNLOCK, &table->printer->p_mutex);
}
