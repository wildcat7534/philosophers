/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   firewatch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:40:40 by cmassol           #+#    #+#             */
/*   Updated: 2025/02/12 01:35:32 by cmassol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	all_eaten(t_table *table);

void	firewatch(void *data, long time_start)
{
	t_table	*table;
	int		i;
	int 	j;
	long	t_eat;
	int		eaten;
	int		k;
	int		dead;
	long	t_die;
	table = (t_table *)data;

	j = 0;
	//printf("****************Firewatch started*******************************\n");
	while (!table->philo_died)
	{
		i = -1;
        dead = 0;
        k = 0;
		t_die = 0;
		while (++i < table->nb_philo)
		{
                safe_mutex(LOCK, &table->philo[i].philo_mutex);
                t_eat = table->philo[i].last_meal_time;
                safe_mutex(UNLOCK, &table->philo[i].philo_mutex);
/*                 safe_mutex(LOCK, &table->philo[i].philo_mutex);
                eaten = table->philo[i].meals_eaten;
                safe_mutex(UNLOCK, &table->philo[i].philo_mutex); */
                safe_mutex(LOCK, &table->philo[i].philo_mutex);
                dead = table->philo[i].died;
                safe_mutex(UNLOCK, &table->philo[i].philo_mutex);
                safe_mutex(LOCK, &table->philo[i].philo_mutex);
				t_die = table->philo[i].time_die;
                safe_mutex(UNLOCK, &table->philo[i].philo_mutex);
				if ((gettime(MILLISECOND) - t_eat >= t_die && t_eat != 0) || dead == 1)
				{
					safe_mutex(LOCK, &table->philo[i].philo_mutex);
					table->philo[i].died = 1;
					printf("%ld %d died\n", gettime(MILLISECOND) - time_start, table->philo[i].id);
					safe_mutex(UNLOCK, &table->philo[i].philo_mutex);
					safe_mutex(LOCK, &table->table_mutex);
					table->philo_died = 1;
					safe_mutex(UNLOCK, &table->table_mutex);
					//ft_usleep(420, table);
					//printf("%sFIREWATCH [Philo : %d died]%s\n", RED, table->philo[i].id, RESET);
					//printf("Philo %d           [%slast meal time %ld%s]\n", table->philo[i].id, RED, gettime(MILLISECOND) - t_eat, RESET);
					break;
				}
				else if (eaten != 0 && eaten >= mtx_table_maxmeals(table->philo) && mtx_table_maxmeals(table->philo) != 0)
				{
                    j = 0;
					while (j < mtx_nb_philo(table->philo))
					{					
						if ( all_eaten(table) == 1 && k < mtx_nb_philo(table->philo))
                        {
                            k = 0;
                            table->philo_died = 1;
                            table->philo[j].died = 1;
                            while (k < table->nb_philo)
                            {
                                printf("Philo: [%d] eat [%d] meals\n", table->philo[k].id, eaten);
                                k++;
                            }
                            printf("%sFIREWATCH [Philo ALL EATEN]%s\n", GREEN, RESET);
                            i = k;
                        }
                        else 
    						j++;
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

	i = -1;
	while (++i < mtx_nb_philo(table->philo))
	{
		safe_mutex(LOCK, &table->philo[i].philo_mutex);
		if (table->philo[i].meals_eaten < mtx_table_maxmeals(table->philo))
		{
			safe_mutex(UNLOCK, &table->philo[i].philo_mutex);
			return (0);
		}
		safe_mutex(UNLOCK, &table->philo[i].philo_mutex);
	}
	return (1);
}
