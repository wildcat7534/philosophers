/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pistons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 21:54:00 by cmassol           #+#    #+#             */
/*   Updated: 2025/01/30 11:34:37 by cmassol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*thd_rte(void *data)
{
	t_philo		*philo;
	philo = (t_philo *)data;

	while (!philo->died && !philo->table->philo_died)
	{
		if (!eat_mutex(philo))
		{
			if (!philo->died && !philo->table->philo_died)
			{
				print_status(philo, "is sleeping", gettime(MILLISECOND));
				ft_usleep(philo->time_sleep * 1000, philo->table);
			}
			else
				return (NULL);
		}
		else
			return (NULL);
		if (philo->meals_eaten >= philo->meals_max && philo->meals_max != 0)
		{
			safe_mutex(UNLOCK, &philo->lfork->fork_mutex);
			safe_mutex(UNLOCK, &philo->rfork->fork_mutex);
			return (NULL);
		}
		print_status(philo, "is thinking", gettime(MILLISECOND));
	}
	safe_mutex(UNLOCK, &philo->lfork->fork_mutex);
	safe_mutex(UNLOCK, &philo->rfork->fork_mutex);
	return (NULL);
}

static int	all_eaten(t_table *table)
{
	int	i;
	i = 0;
	while (i < table->nb_philo)
	{
		if (table->philo[i].meals_eaten < table->meals_max)
			return (0);
		i++;
	}
	return (1);
}

void	firewatch(void *data, long time_start)
{
	t_table	*table;
	int		i;
	long	cur_time;

	table = (t_table *)data;
	printf("****************Firewatch started*******************************\n");
	while (!table->philo_died)
	{
		i = -1;
		while (++i < table->nb_philo)
		{
			//if (gettime(MILLISECOND)+ sleep - table->philo[i].last_meal_time.tv_sec >= table->time_die)
			cur_time = gettime(MILLISECOND) - time_start;
			//printf("\n current time %ld && Philo %d last meal time %ld\n", cur_time, table->philo[i].id, cur_time - table->philo[i].last_meal_time.tv_sec);
			if (cur_time - table->philo[i].t_meal.tv_sec >= table->time_die)
			{
				//safe_mutex(LOCK, &table->table_mutex);
				table->philo[i].died = 1;
				table->philo_died = 1;
				//ft_usleep(300000);
				printf("%sFIREWATCH [Philo : %d died]%s\n", RED, table->philo[i].id, RESET);
				printf("current time %ld\n", cur_time);
				printf("Philo %d last meal time %ld\n", table->philo[i].id, cur_time - table->philo[i].t_meal.tv_sec);
				//safe_mutex(UNLOCK, &table->table_mutex);
				break;
			}
			else if (table->meals_max != 0 && table->philo[i].meals_eaten >= table->meals_max)
			{
				while (i < table->nb_philo)
				{					
					if ( all_eaten(table) == 1)
						{
							i = 0;
							table->philo_died = 1;
							table->philo[i].died = 1;
							while (i < table->nb_philo)
							{
								printf("Philo: [%d] eat [%d] meals\n", table->philo[i].id, table->philo[i].meals_eaten);
								i++;
							}
								printf("%sFIREWATCH [Philo ALL EATEN]%s\n", GREEN, RESET);
						}
					i++;
				}
				//safe_mutex(UNLOCK, &table->table_mutex);
			}
			//ft_usleep(100000); // Attendre un peu avant de vérifier à nouveau
		}
		//ft_usleep(1); // Attendre un peu avant de vérifier à nouveau
	}
	printf("*******************************************************Firewatch ended**********************************\n");
	return ;
}
