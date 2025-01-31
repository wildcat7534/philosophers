/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 01:03:59 by cmassol           #+#    #+#             */
/*   Updated: 2025/01/31 06:08:05 by cmassol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int arc, char **argv)
{
	t_table			*table;

	table = (t_table *)malloc(sizeof(t_table));
	if (arc < 5 || arc > 6)
	{
		printf("Usage: [%snb_Philo%s] [%stime_die%s] [%stime_eat%s] [%stime_sleep%s] [%snb_meals%s]\n",
			YELLOW, RESET, YELLOW, RESET, YELLOW, RESET, YELLOW, RESET, YELLOW,
			RESET);
		return (1);
	}
	if ((check_argv_positivity(argv)))
	{
		printf("%sError%s: nb-> not positive, number, < int\n", RED, RESET);
		return (1);
	}
	table->nb_philo = ft_atoi(argv[1]);
	table->time_die = ft_atoi(argv[2]);
	table->time_eat = ft_atoi(argv[3]);
	table->time_sleep = ft_atoi(argv[4]);
	if (arc == 6)
		table->meals_max = ft_atoi(argv[5]);
	else
		table->meals_max = 0;
	init_philosophers(table);
	if (start_simulation(table))
	{
		printf("(MAIN) Error: simulation failed\n");
		return (1);
	}
	printf("MAIN : Simulation ended : %ld\n", gettime(MILLISECOND) - table->t_start);
	pthread_mutex_destroy(&table->table_mutex);
	pthread_mutex_destroy(&table->forks->fork_mutex);
	pthread_mutex_destroy(&table->philo->philo_mutex);
	pthread_mutex_destroy(&table->table_mutex);
	free(table->philo);
	free(table->forks);
	free(table);
	return (0);
}

// TODO :

// parsing V
// repas max V
// norm
// makefile V
// valgrind v0.10
// modulo %2 == 0 pour le nb de philo pair
