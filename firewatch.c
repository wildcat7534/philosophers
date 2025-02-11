/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   firewatch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:40:40 by cmassol           #+#    #+#             */
/*   Updated: 2025/02/11 15:49:41 by cmassol          ###   ########.fr       */
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

	table = (t_table *)data;
    int maxmeal = table->meals_max;
	//printf("****************Firewatch started*******************************\n");
	while (!table->philo_died)
	{
		i = -1;
        dead = 0;
        k = 0;
		while (++i < table->nb_philo)
		{
                safe_mutex(LOCK, &table->philo[i].philo_mutex);
                t_eat = table->philo[i].last_meal_time;
                eaten = table->philo[i].meals_eaten;
                dead = table->philo[i].died;
                safe_mutex(UNLOCK, &table->philo[i].philo_mutex);
				if ((gettime(MILLISECOND) - t_eat >= table->philo[i].time_die && t_eat != 0) || dead == 1)
				{
					table->philo[i].died = 1;
					table->philo_died = 1;
					ft_usleep(420, table);
					printf("%sFIREWATCH [Philo : %d died]%s\n", RED, table->philo[i].id, RESET);
					printf("current time %ld\n", gettime(MILLISECOND) - time_start);
					printf("Philo %d           [%slast meal time %ld%s]\n", table->philo[i].id, RED, gettime(MILLISECOND) - t_eat, RESET);
					break;
				}
				else if (eaten != 0 && eaten >= maxmeal && maxmeal != 0)
				{
                    j = 0;
					while (j < table->nb_philo)
					{					
						if ( all_eaten(table) == 1 && k < table->nb_philo)
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
	}
	//printf("*******************************************************Firewatch ended**********************************\n");
	return ;
}
static int	all_eaten(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nb_philo)
	{
		safe_mutex(LOCK, &table->philo[i].philo_mutex);
		if (table->philo[i].meals_eaten < table->meals_max)
		{
			safe_mutex(UNLOCK, &table->philo[i].philo_mutex);
			return (0);
		}
		safe_mutex(UNLOCK, &table->philo[i].philo_mutex);
	}
	return (1);
}