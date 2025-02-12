/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 00:37:51 by cmassol           #+#    #+#             */
/*   Updated: 2025/02/12 21:25:56 by cmassol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	nb;

	i = 0;
	nb = 0;
	if (!str)
		return (0);
	if (ft_strlen(str) > 11)
		return (-1);
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		return (-1);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb);
}

void ft_itoa(long n, char *str)
{
    int i = 0;
    int is_negative = 0;

    if (n == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }
    if (n < 0) {
        is_negative = 1;
        n = -n;
    }
    while (n != 0) {
        str[i++] = (n % 10) + '0';
        n = n / 10;
    }
    if (is_negative)
        str[i++] = '-';
    str[i] = '\0';
	str = reverse(str);
}

char *reverse(char *str)
{
	int i = 0;
	int j = ft_strlen(str) - 1;
	char temp;

	while (i < j) {
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
	return (str);
}


int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	check_argv_positivity(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) < 1)
			return (1);
		i++;
	}
	return (0);
}

void	ft_free(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nb_philo)
	{
		//ft_usleep(10000, table);
		pthread_mutex_destroy(&table->philo[i].lfork->fork_mutex);
		pthread_mutex_destroy(&table->philo[i].philo_mutex);
	}
	pthread_mutex_destroy(&table->table_mutex);
	free(table->philo);
	free(table->forks);
	free(table);
}

unsigned int mtx_read_id(t_philo *philo)
{
	unsigned int	id;
	safe_mutex(LOCK, &philo->philo_mutex);
	id = philo->id;
	safe_mutex(UNLOCK, &philo->philo_mutex);
	return (id);
}

long mtx_p_t_start(t_philo *philo)
{
	long	t_start;
	safe_mutex(LOCK, &philo->philo_mutex);
	t_start = philo->t_start;
	safe_mutex(UNLOCK, &philo->philo_mutex);
	return (t_start);
}

int mtx_stop_sim_read(t_philo *philo)
{
	int	stop_sim;
	safe_mutex(LOCK, &philo->philo_mutex);
	stop_sim = philo->stop_simulation;
	safe_mutex(UNLOCK, &philo->philo_mutex);
	return (stop_sim);
}

void mtx_stop_sim_write(t_philo *philo)
{
	safe_mutex(LOCK, &philo->philo_mutex);
	philo->stop_simulation = 1;
	safe_mutex(UNLOCK, &philo->philo_mutex);
}

int mtx_meal_eat_philo(t_philo *philo)
{
	int	meal_eat;
	safe_mutex(LOCK, &philo->philo_mutex);
	meal_eat = philo->meals_eaten;
	safe_mutex(UNLOCK, &philo->philo_mutex);
	return (meal_eat);
}

long mtx_last_meal_time(t_philo *philo)
{
	long	last_meal_time;
	safe_mutex(LOCK, &philo->philo_mutex);
	last_meal_time = philo->last_meal_time;
	safe_mutex(UNLOCK, &philo->philo_mutex);
	return (last_meal_time);
}

int mtx_p_max_meals(t_philo *philo)
{
	int	p_max_meals;
	safe_mutex(LOCK, &philo->philo_mutex);
	p_max_meals = philo->meals_max;
	safe_mutex(UNLOCK, &philo->philo_mutex);
	return (p_max_meals);
}


// TABLE MUTEX /////////////////////////////////////////////

int mtx_table_maxmeals(t_table *table)
{
	int	t_max_meals;
	safe_mutex(LOCK, &table->table_mutex);
	t_max_meals = table->meals_max;
	safe_mutex(UNLOCK, &table->table_mutex);
	return (t_max_meals);
}

int	mtx_tnb_philo(t_table *table)
{
	int	t_nb_philo;
	safe_mutex(LOCK, &table->table_mutex);
	t_nb_philo = table->nb_philo;
	safe_mutex(UNLOCK, &table->table_mutex);
	return (t_nb_philo);
}

long mtx_table_tdie(t_table *table)
{
	long	t_die;
	safe_mutex(LOCK, &table->table_mutex);
	t_die = table->time_die;
	safe_mutex(UNLOCK, &table->table_mutex);
	return (t_die);
}