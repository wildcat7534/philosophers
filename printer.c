/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:34:35 by cmassol           #+#    #+#             */
/*   Updated: 2025/02/16 20:47:38 by cmassol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	error(char *msg)
{
	printf("[%sError: %s%s]\n", RED, msg, RT);
	return (1);
}

/*void	fprinter(long time, int id, char *status, t_table *table)
{
	char	buffer[256];
	int		offset;
	char	temp[20];
	int		len;

	safe_mutex(LOCK, &table->printer->p_mutex);
	table->printer->buffer = buffer;
	offset = 0;
	ft_itoa(gettime(MILLISECOND) - time, temp);
	len = strlen(temp);
	memcpy(buffer + offset, temp, len);
	offset += len;
	buffer[offset++] = ' ';
	ft_itoa(id, temp);
	len = strlen(temp);
	memcpy(buffer + offset, temp, len);
	offset += len;
	buffer[offset++] = ' ';
	len = ft_strlen(status);
	memcpy(buffer + offset, status, len);
	offset += len;
	buffer[offset++] = '\n';
	//safe_mutex(UNLOCK, &table->printer->p_mutex);

	safe_mutex(LOCK, &table->printer->p_mutex);
	table->printer->status = buffer;
	safe_mutex(UNLOCK, &table->printer->p_mutex);

}
*/

void	fprinter(long time, int id, char *status, t_table *table)
{
	/*int len = ft_strlen(status);
	char *buffer = malloc(len + 1);
	memcpy(buffer, status, len);
	buffer[len] = '\0';
	table->printer->status = buffer;
*/
	safe_mutex(LOCK, &table->table_mutex);
	int stop_sim = table->stop_simulation;
	//safe_mutex(UNLOCK, &table->table_mutex);
	//safe_mutex(LOCK, &table->table_mutex);
	int philo_died = table->philo_died;
	//safe_mutex(UNLOCK, &table->table_mutex);
	//safe_mutex(LOCK, &table->table_mutex);
	int nb_philo = table->nb_philo;
	safe_mutex(UNLOCK, &table->table_mutex);

	if (philo_died == 0 || stop_sim == 0 || nb_philo == 1)
	{
		//printf("%ld %d %s\n", gettime(MILLISECOND) - time, id, status);
		if (ft_strcmp(status, "died") == 0)
		{
			m_die_w(table);
			all_stop_simulation(table);
			//ft_usleep(1000, table);
			
			safe_mutex(LOCK, &table->printer->p_mutex);
			printf("%ld %d %s\n", gettime(MILLISECOND) - time, id, status);
			//write(1, table->printer->status, offset);
			safe_mutex(UNLOCK, &table->printer->p_mutex);
		}
		else
		{
			safe_mutex(LOCK, &table->printer->p_mutex);
			printf("%ld %d %s\n", gettime(MILLISECOND) - time, id, status);
			//write(1, table->printer->status, offset);
			safe_mutex(UNLOCK, &table->printer->p_mutex);
		}
	}

}
	