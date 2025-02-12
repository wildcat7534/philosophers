/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   firewatch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:40:40 by cmassol           #+#    #+#             */
/*   Updated: 2025/02/12 17:09:30 by cmassol          ###   ########.fr       */
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
	int		k;
	long	t_eat;
	int		eaten;
	long	t_die;
	int		nb_philo;
	int		end_simulation;
	
	table = (t_table *)data;
	end_simulation = 0;
	nb_philo = mtx_tnb_philo(table);
	t_die = mtx_table_tdie(table);
	eaten = mtx_table_maxmeals(table);
	
	//printf("****************Firewatch started*******************************\n");
	while (!end_simulation)
	{
		i = -1;
		while (++i < nb_philo)
		{
				t_eat = mtx_last_meal_time(&table->philo[i]);

				if ((gettime(MILLISECOND) - t_eat >= t_die && t_eat != 0))
				{
					printf("%ld %d died\n", gettime(MILLISECOND) - time_start, mtx_read_id(&table->philo[i]));
					all_stop_simulation(table);
					end_simulation = 1;
					//table->philo[i].died = 1;
					//ft_usleep(420, table);
					//printf("%sFIREWATCH [Philo : %d died]%s\n", RED, table->philo[i].id, RESET);
					//printf("Philo %d           [%slast meal time %ld%s]\n", table->philo[i].id, RED, gettime(MILLISECOND) - t_eat, RESET);
					break;
				}
				else if (eaten != 0)
				{
                    j = -1;
					while (++j < nb_philo)
					{					
						if ( all_eaten(table) == 1)
                        {
							
							//table->philo_died = 1;
                            //table->philo[j].died = 1;
							all_stop_simulation(table);
							return ;
							//j = nb_philo;
							///DEBUG PRINT////////////////////////
								k = 0;
								while (k < table->nb_philo)
								{
									eaten = mtx_meal_eat_philo(&table->philo[k]);
									int id = mtx_read_id(&table->philo[k]);
									printf("Philo: [%d] eat [%d] meals\n", id, eaten);
									k++;
								}
								printf("%sFIREWATCH [Philo ALL EATEN]%s\n", GREEN, RESET);
							///DEBUG PRINT////////////////////////
                        }
					}
			}
		}
		//ft_usleep(1000, table);
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
		mtx_stop_sim_write(&table->philo[i]);
}
