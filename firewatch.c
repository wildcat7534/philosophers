/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   firewatch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:40:40 by cmassol           #+#    #+#             */
/*   Updated: 2025/02/14 17:31:01 by cmassol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	all_eaten(t_table *table);
static void all_stop_simulation(t_table *table);

void	firewatch(void *data, long time_start)
{
	t_table	*table;
	int		i;
	int 	j;
	long	t_eat;
	int		eatmax;
	long	t_die;
	int		nb_philo;
	int		end_simulation;
	
	table = (t_table *)data;
	end_simulation = 0;
	nb_philo = mtx_tnb_philo(table);
	t_die = mtx_table_tdie(table);
	eatmax = mtx_table_maxmeals(table);
	
	int sleep = 0;
	while (!end_simulation)
	{
		i = -1;
		while (nb_philo == 1)
		{
			t_eat = mtx_last_meal_time(&table->philo[0]);
			if ((gettime(MILLISECOND) - time_start) - t_eat >= t_die)
			{
				printf("%ld %d died\n", gettime(MILLISECOND) - time_start, mtx_read_id(&table->philo[0]));
				all_stop_simulation(table);
				end_simulation = 1;
				break;
			}
			ft_usleep(1000);
		}
		while (++i < nb_philo)
		{
			if (nb_philo == 200 && eatmax == 0)
				{
					sleep = 500;
					ft_usleep(sleep);
				}
				t_eat = mtx_last_meal_time(&table->philo[i]);
				if ((gettime(MILLISECOND) - t_eat >= t_die && t_eat != 0))
				{
					printf("%ld %d died\n", gettime(MILLISECOND) - time_start, mtx_read_id(&table->philo[i]));
					all_stop_simulation(table);
					end_simulation = 1;
					break;
				}
				else if (eatmax != 0)
				{
					j = -1;
					while (++j < nb_philo)
					{					
						//ft_usleep(20);
						if ( all_eaten(table) == 1)
                        {
							all_stop_simulation(table);
							return ;
							///DEBUG PRINT////////////////////////
							/* 
							int		k;
							k = -1;
							while (++k < table->nb_philo)
							{
								eaten = mtx_meal_eat_philo(&table->philo[k]);
								int id = mtx_read_id(&table->philo[k]);
								if (eaten != mtx_p_max_meals(&table->philo[k]))
									printf("%sPhilo: [%d] eat only [%d] meals%s\n", RED, id, eaten, RESET);
								else
									printf("%sPhilo: [%d] eat [%d] meals%s\n", GREEN, id, eaten, RESET);
							} */
							///DEBUG PRINT////////////////////////
                        }
					}
			}
		}
	}
	return ;
}
static int	all_eaten(t_table *table)
{
	int	i;
	int max_meals;
	int nb_philo;
	i = -1;
	
	nb_philo = mtx_tnb_philo(table);
	max_meals = mtx_table_maxmeals(table);
	while (++i < nb_philo)
	{
		ft_usleep(12);
		if (mtx_meal_eat_philo(&table->philo[i]) < max_meals)
			return (0);
	}
	return (1);
}

static void all_stop_simulation(t_table *table)
{
	int	i;
	int nb_philo = mtx_tnb_philo(table);
	i = -1;
	while (++i < nb_philo)
	{
		mtx_stop_sim_write(&table->philo[i]);
	}
}
