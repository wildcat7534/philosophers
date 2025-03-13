/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 01:03:59 by cmassol           #+#    #+#             */
/*   Updated: 2025/03/09 00:41:31 by cmassol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	arg_is_digit(char *arg);
static int	ft_isdigit(int c);

int	main(int arc, char **argv)
{
	int	i;

	if (arc < 5 || arc > 6 || check_argv_positivity(argv))
	{
		printf("Usage: [%sPhilo%s] [%sdie%s] [%seat%s] [%ssleep%s] [%smeal%s]\n",
			YW, RT, YW, RT, YW, RT, YW, RT, YW, RT);
		if (check_argv_positivity(argv))
			printf("%sError%s: nb-> not positive, number, < int\n", RED, RT);
		return (1);
	}
	i = 0;
	while (++i < arc)
	{
		if (!arg_is_digit(argv[i]))
		{
			printf(RED"Error : not a digit or integer\n"RT);
			return (1);
		}
	}
	if (start_simulation(init_philosophers(arc, argv)))
	{
		printf("(MAIN) Error: simulation failed\n");
		return (1);
	}
	return (0);
}

static int	arg_is_digit(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
	}
	return (1);
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
