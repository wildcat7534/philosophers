/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:34:35 by cmassol           #+#    #+#             */
/*   Updated: 2025/02/12 21:27:05 by cmassol          ###   ########.fr       */
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

// write a printer with write instead of printf
// using this base printf("%ld %d is eating\n", gettime(MILLISECOND) - t_start, id);
/* void printer(long time, int id, char *status)
{
	write(1, &time, sizeof(long));
	write(1, " ", 1);
	write(1, &id, sizeof(int));
	write(1, " ", 1);
	write(1, status, ft_strlen(status));
} */

void printer(long time, int id, char *status)
{
    char buffer[256];
    int offset = 0;
    char temp[20];

    // Convert time to string and copy to buffer
    ft_itoa(time, temp);
    int len = strlen(temp);
    memcpy(buffer + offset, temp, len);
    offset += len;

    // Add space
    buffer[offset++] = ' ';

    // Convert id to string and copy to buffer
    ft_itoa(id, temp);
    len = strlen(temp);
    memcpy(buffer + offset, temp, len);
    offset += len;

    // Add space
    buffer[offset++] = ' ';

    // Copy status to buffer
    len = ft_strlen(status);
    memcpy(buffer + offset, status, len);
    offset += len;

    // Add newline
    buffer[offset++] = '\n';

    // Write the buffer to stdout
    write(1, buffer, offset);
}
