/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   firewatch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:40:40 by cmassol           #+#    #+#             */
/*   Updated: 2025/02/07 13:46:18 by cmassol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	all_eaten(t_table *table);

void	firewatch(void *data, long time_start)
{
	t_table	*table;
	int		i;
	int j = 0;
	//long	cur_time;

	table = (t_table *)data;
	printf("****************Firewatch started*******************************\n");
	//safe_mutex(LOCK, &table->table_mutex);
	while (!table->philo_died )
	{
		i = -1;
		long t_eat;
		while (++i < table->nb_philo)
		{
            
			//cur_time = gettime(MILLISECOND) - cur_time;
			//if (gettime(MILLISECOND)+ sleep - table->philo[i].last_meal_time.tv_sec >= table->time_die)
			//printf("current time %ld\n", gettime(MILLISECOND) - cur_time);
			//safe_mutex(LOCK, &table->philo[i].philo_mutex);
			//printf("\n current time %ld && Philo %d last meal time %ld\n, table->philo[i].last_meal_time - cur_time, table->philo[i].id, table->philo[i].last_meal_time - cur_time);
			//if (gettime(MILLISECOND) - table->philo[i].last_meal_time > 299)
			//	printf("Philo %d           [%s-last meal time %ld-%s]\n", table->philo[i].id, RED, gettime(MILLISECOND) - table->philo[i].last_meal_time, RESET);
			//safe_mutex(UNLOCK, &table->philo[i].philo_mutex);
			//ft_usleep(1000, table);
/* 			while (safe_mutex(LOCK, &table->philo[i].philo_mutex) == 0)
			 { */
                safe_mutex(LOCK, &table->philo[i].philo_mutex);
                t_eat = table->philo[i].last_meal_time;
                //printf("%st_eat : %s %ld\n",BPURPLE, RESET, t_eat);
				///printf("Philo %d           [%slast meal time %ld%s]\n", table->philo[i].id, RED, gettime(MILLISECOND) - t_eat, RESET);
                safe_mutex(UNLOCK, &table->philo[i].philo_mutex);
				if ( gettime(MILLISECOND) - t_eat >= table->philo[i].time_die && t_eat != 0)
				{
					//safe_mutex(LOCK, &table->table_mutex);
					table->philo[i].died = 1;
					table->philo_died = 1;
					ft_usleep(4200, table);
					printf("%sFIREWATCH [Philo : %d died]%s\n", RED, table->philo[i].id, RESET);
					printf("current time %ld\n", gettime(MILLISECOND) - time_start);
					printf("Philo %d           [%slast meal time %ld%s]\n", table->philo[i].id, RED, gettime(MILLISECOND) - t_eat, RESET);
					//safe_mutex(UNLOCK, &table->philo[i].philo_mutex);
					break;
					//safe_mutex(UNLOCK, &table->philo[i].philo_mutex);
					//safe_mutex(UNLOCK, &table->table_mutex);
				}
				else if (table->philo[i].meals_max != 0 && table->philo[i].meals_eaten >= table->philo[i].meals_max)
				{
					while (j < table->nb_philo)
					{					
						if ( all_eaten(table) == 1)
							{
								j = 0;
/* 								table->philo_died = 1;
								table->philo[j].died = 1; */
								while (j < table->nb_philo)
								{
									printf("Philo: [%d] eat [%d] meals\n", table->philo[j].id, table->philo[j].meals_eaten);
									j++;
								}
									printf("%sFIREWATCH [Philo ALL EATEN]%s\n", GREEN, RESET);
							}
						j++;
					//safe_mutex(UNLOCK, &table->philo[i].philo_mutex);
					}
					//break;
				//}
			}
			//safe_mutex(UNLOCK, &table->philo[i].philo_mutex);
	//safe_mutex(UNLOCK, &table->table_mutex);
			//safe_mutex(UNLOCK, &table->philo[i].philo_mutex);
		}
				//safe_mutex(UNLOCK, &table->philo[i].philo_mutex);
	}
	//safe_mutex(UNLOCK, &table->table_mutex);
	printf("*******************************************************Firewatch ended**********************************\n");
	return ;
}
static int	all_eaten(t_table *table)
{
	int	i;
	i = -1;
	//safe_mutex(LOCK, &table->table_mutex);
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
	//safe_mutex(UNLOCK, &table->table_mutex);
	return (1);
}