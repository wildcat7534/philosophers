/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   firewatch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:40:40 by cmassol           #+#    #+#             */
/*   Updated: 2025/03/08 09:55:38 by cmassol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static long	gt(void);
static int	nb_philo_one(t_table *table, long t_s);
static int	eatmax_all(t_table *table);
static int	firewatch_engine(t_table *table, long t_die, long t_s);

void	firewatch(void *data, long t_s)
{
	t_table	*table;
	int		i;
	long	t_die;

	table = (t_table *)data;
	t_die = mtx_table_tdie(table) / 1000;
	while (!table->stop_simulation)
	{
		i = -1;
		if (nb_philo_one(table, t_s))
			return ;
		if (firewatch_engine(table, t_die, t_s))
			return ;
	}
	return ;
}

static int	firewatch_engine(t_table *table, long t_die, long t_s)
{
	int		i;
	long	t_eat;
	int		maxmeal;
	int		nb_philo;

	nb_philo = mtx_tnb_philo(table);
	maxmeal = mtx_table_maxmeals(table);
	i = -1;
	while (++i < nb_philo)
	{
		ft_usleep(10, table);
		t_eat = mtx_last_meal_time(&table->philo[i]);
		if ((gt() - t_eat >= t_die && t_eat != 0))
		{
			all_stop_simulation(table);
			fprinter(t_s, m_id(&table->philo[i]), "died", table);
			return (1);
		}
		else if (maxmeal != 0)
		{
			if (eatmax_all(table) == 1)
				return (1);
		}
	}
	return (0);
}

static int	eatmax_all(t_table *table)
{
	int	i;
	int	max_meals;
	int	nb_philo;

	nb_philo = mtx_tnb_philo(table);
	max_meals = mtx_table_maxmeals(table);
	i = -1;
	while (++i < nb_philo)
	{
		if (all_eaten(table) == 1)
		{
			all_stop_simulation(table);
			return (1);
		}
	}
	return (0);
}

static int	nb_philo_one(t_table *table, long t_s)
{
	int	nb_philo;
	int	t_die;

	t_die = mtx_table_tdie(table) / 1000;
	nb_philo = mtx_tnb_philo(table);
	while (nb_philo == 1)
	{
		if ((el_st(t_s)) >= t_die)
		{
			fprinter(t_s, 1, "died", table);
			m_die_w(table);
			all_stop_simulation(table);
			return (1);
		}
		ft_usleep(1000, table);
	}
	return (0);
}

static long	gt(void)
{
	return (gettime(MILLISECOND));
}
