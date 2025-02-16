/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 01:03:59 by cmassol           #+#    #+#             */
/*   Updated: 2025/02/16 07:59:23 by cmassol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int arc, char **argv)
{
	if (arc < 5 || arc > 6 || check_argv_positivity(argv))
	{
		printf("Usage: [%sPhilo%s] [%sdie%s] [%seat%s] [%ssleep%s] [%smeal%s]\n",
			YELLOW, RT, YELLOW, RT, YELLOW, RT, YELLOW, RT, YELLOW,
			RT);
		if (check_argv_positivity(argv))
			printf("%sError%s: nb-> not positive, number, < int\n", RED, RT);
		return (1);
	}
	if (start_simulation(init_philosophers(arc, argv)))
	{
		printf("(MAIN) Error: simulation failed\n");
		return (1);
	}
	return (0);
}
