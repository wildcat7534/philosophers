/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 01:03:59 by cmassol           #+#    #+#             */
/*   Updated: 2025/02/13 15:45:53 by cmassol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int arc, char **argv)
{
	long t_start = gettime(MILLISECOND);
	if (arc < 5 || arc > 6 || check_argv_positivity(argv))
	{
		printf("Usage: [%sPhilo%s] [%sdie%s] [%seat%s] [%ssleep%s] [%smeal%s]\n",
			YELLOW, RESET, YELLOW, RESET, YELLOW, RESET, YELLOW, RESET, YELLOW,
			RESET);
		if (check_argv_positivity(argv))
			printf("%sError%s: nb-> not positive, number, < int\n", RED, RESET);
		return (1);
	}

	if (start_simulation(init_philosophers(arc, argv)))
	{
		printf("(MAIN) Error: simulation failed\n");
		return (1);
	}
	(void)t_start;
	//printf("MAIN : Simulation ended : %ld\n", gettime(MILLISECOND) - t_start);
	//printf("MAIN : Simulation ended ms : %ld\n", gettime(MILLISECOND));
	return (0);
}

// TODO :

// parsing V
// repas max V
// norm
// makefile V
// valgrind v0.10
// modulo %2 == 0 pour le nb de philo pair v
// PRINT FOURCHETTE TAKEN v
// PRINT PHILO IS EATING etc v

// 1 philo a gerer
// temps a gerer

