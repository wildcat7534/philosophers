/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 23:34:25 by cmassol           #+#    #+#             */
/*   Updated: 2025/01/30 11:06:10 by cmassol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h> // TODO: remove this peut etre
# include <time.h>
# include <unistd.h>

// color codes
# define RED "\x1b[31m"
# define BRED "\x1b[91m"
# define GREEN "\x1b[32m"
# define BGREEN "\x1b[92m"
# define YELLOW "\x1b[33m"
# define BYELLOW "\x1b[93m"
# define BLUE "\x1b[34m"
# define BBLUE "\x1b[94m"
# define PURPLE "\x1b[35m"
# define BPURPLE "\x1b[95m"
# define CYAN "\x1b[36m"
# define BCYAN "\x1b[96m"
# define RESET "\x1b[0m"

typedef enum e_malloc
{
	MALLOC_PHILOSOPHERS,
	MALLOC_FORKS,
}			t_smalloc;

typedef enum e_code_mtx
{
	INIT,
	LOCK,
	UNLOCK,
	DESTROY,
}			t_code_mtx;

typedef enum e_code_thread
{
	JOIN,
	CREATE,
	DETACH,
}			t_code_thread;

typedef enum e_time_val
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}			t_time_val;

typedef enum e_status
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD,
}			t_status;

typedef pthread_mutex_t	t_mtx;

typedef struct s_forks
{
	pthread_mutex_t				fork_mutex;
	int					fork_id;
}						t_forks;

typedef struct s_table
{
	pthread_t			tid;
	int					nb_philo;
	unsigned int		time_die;
	double				time_eat;
	unsigned int		time_sleep;
	int					meals_max;
	int					meals_eaten;
	int					philo_died;
	long				t_start;
	t_forks				*forks;
	pthread_mutex_t		table_mutex;
	struct s_philo		*philo;
}						t_table;

typedef struct s_philo
{
	unsigned int		id;
	pthread_t			tid;
	unsigned int		time_die;
	unsigned int		time_eat;
	unsigned int		time_sleep;
	int					meals_max;
	int					meals_eaten;
	int					died;
	struct timeval		t_meal;
	t_forks				*lfork;
	t_forks				*rfork;
	pthread_mutex_t		philo_mutex; //TODO a verifier
	struct s_table		*table;
	struct s_philo		*next;
}						t_philo;


typedef struct s_time
{
	time_t				tv_sec;
	suseconds_t			tv_usec;
}						t_time;

void					*thd_rte(void *data);
void					init_table(t_table *table, int argc, char **argv);
void					init_philosophers(t_table *table);
void					init_forks(t_table *table);
int						start_simulation(t_table *table);
int						ft_atoi(const char *str);
int						ft_strcmp(const char *s1, const char *s2);
void					ft_mutex(t_philo *philo, pthread_mutex_t *philo_mutex);
int						eat_mutex(t_philo *philo);
void					print_status(t_philo *philo, char *status, long time);
long long				get_time_diff(struct timespec start, struct timespec end);
long					get_elapsed_time_microseconds(struct timeval start, struct timeval end);
void					ft_usleep(long usec, t_table *table);
int						error(char *msg);
int						safe_mutex(t_code_mtx code, t_mtx *mutex);
int						safe_thread(t_code_thread code, t_philo *philo, void *(*)(void *));
void					safe_malloc(t_smalloc code, t_table *table);
long					gettime(t_time_val time_val);
int						ft_times_up(int time);
void					firewatch(void *data, long time_start);
int						check_argv_positivity(char **argv);
int						ft_strlen(const char *str);

#endif