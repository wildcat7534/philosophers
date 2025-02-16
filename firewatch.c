/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   firewatch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:40:40 by cmassol           #+#    #+#             */
/*   Updated: 2025/02/16 18:33:04 by cmassol          ###   ########.fr       */
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
	long	te;
	int		id;

	i = -1;
	while (++i < mtx_tnb_philo(table))
	{
		id = m_id(&table->philo[i]);
		if (mtx_tnb_philo(table) > 131 && mtx_tnb_philo(table) != 199)
			ft_usleep(2000, table);
		else
			ft_usleep(100, table);
		
		te = mtx_last_meal_time(&table->philo[i]);
		if ((gt() - te >= t_die && te != 0) /*|| el_st(t_s) - te >= t_die*/)
		{
			//printf("%ld %d died\n", el_st(t_s), m_id(&table->philo[i]));
			//safe_mutex(LOCK, &table->printer->p_mutex);
			fprinter(t_s, id , "died", table);
			//safe_mutex(UNLOCK, &table->printer->p_mutex);
			all_stop_simulation(table);
			table->stop_simulation = 1;
			return (1);
		}
		else if (mtx_table_maxmeals(table) != 0 && eatmax_all(table) == 1)
			return (1);
	}
	return (0);
}

static int	eatmax_all(t_table *table)
{
	int	i;
	int	max_meals;
	int	nb_philo;

	i = -1;
	nb_philo = mtx_tnb_philo(table);
	max_meals = mtx_table_maxmeals(table);
	while (++i < nb_philo)
	{
		if (all_eaten(table) == 1)
		{
			printf("All philosophers have eaten %d meals\n", max_meals);
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
	//int	time_eat;

	t_die = mtx_table_tdie(table) / 1000;
	nb_philo = mtx_tnb_philo(table);
	while (nb_philo == 1)
	{
		//time_eat = mtx_last_meal_time(&table->philo[0]);
		if ((el_st(t_s)) >= t_die)
		{
			fprinter(t_s, 1 , "died", table);
			//printf("%ld %d died\n", el_st(t_s), m_id(&table->philo[0]));
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
