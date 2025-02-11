/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:34:35 by cmassol           #+#    #+#             */
/*   Updated: 2025/02/11 16:26:30 by cmassol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	error(char *msg)
{
	printf("[%sError: %s%s]\n", RED, msg, RESET);
	return (1);
}

void	print_status(t_philo *philo, char *status, long time)
{
	char *smiley;
	time = time - philo->table->t_start;

	if (ft_strcmp(status, "is eating") == 0)
		smiley = "😋🍽️";
	else if (ft_strcmp(status, "is sleeping") == 0)
		smiley = "😴";
	else if (ft_strcmp(status, "is thinking") == 0)
		smiley = "🤔";
	else if (ft_strcmp(status, "has died") == 0)
		smiley = "💀";
	else
		smiley = "🤷";
	if (philo->id == 1)
		printf("%ld : %sPhilosopher%s [%s%d%s] %s\n", time, BRED, RESET, RED,
			philo->id, RESET, smiley);
	else if (philo->id == 2)
		printf("%ld : %sPhilosopher%s [%s%d%s] %s\n", time, BGREEN, RESET, GREEN,
			philo->id, RESET, smiley);
	else if (philo->id == 3)
		printf("%ld : %sPhilosopher%s [%s%d%s] %s\n", time, BBLUE, RESET, BLUE,
			philo->id, RESET, smiley);
	else if (philo->id == 4)
		printf("%ld : %sPhilosopher%s [%s%d%s] %s\n", time, BPURPLE, RESET, PURPLE,
			philo->id, RESET, smiley);
	else if (philo->id == 5)
		printf("%ld : %sPhilosopher%s [%s%d%s] %s\n", time, BCYAN, RESET, CYAN,
			philo->id, RESET, smiley);
	else
		printf("%ld : %sPhilosopher%s [%s%d%s] %s\n", time, BYELLOW, RESET, YELLOW,
			philo->id, RESET, smiley);
}

void	printer(long time, t_philo *philo, char *status)
{
	safe_mutex(LOCK, &philo->table->table_mutex);
	printf("%ld %d %s\n", time - philo->table->t_start, philo->id, status);
	safe_mutex(UNLOCK, &philo->table->table_mutex);
}
