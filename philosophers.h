/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 23:34:25 by cmassol           #+#    #+#             */
/*   Updated: 2025/03/08 01:33:46 by cmassol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
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
# define RT "\x1b[0m"

typedef enum e_malloc
{
	MALLOC_PHILOSOPHERS,
	MALLOC_FORKS,
	MALLOC_TABLE,
	MALLOC_PRINTER,
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
}			t_c_th;

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

typedef struct s_printer
{
	pthread_mutex_t		p_mutex;
	char				*status;
	char				*buffer;
}						t_printer;

typedef struct s_forks
{
	pthread_mutex_t		fork_mutex;
	int					fork_id;
}						t_forks;

typedef struct s_table
{
	pthread_t			tid;
	int					stop_simulation;
	int					nb_philo;
	long				time_die;
	long				time_eat;
	long				time_sleep;
	int					meals_max;
	int					meals_eaten;
	int					philo_died;
	long				t_start;
	t_forks				*forks;
	pthread_mutex_t		table_mutex;
	struct s_printer	*printer;
	struct s_philo		*philo;
}						t_table;

typedef struct s_philo
{
	int					stop_simulation;
	long				t_start;
	unsigned int		id;
	pthread_t			tid;
	long				time_die;
	long				time_eat;
	long				time_sleep;
	int					meals_max;
	int					meals_eaten;
	int					nb_philo;
	int					died;
	struct timeval		t_meal;
	long				last_meal_time;
	t_forks				*lfork;
	t_forks				*rfork;
	pthread_mutex_t		philo_mutex;
	struct s_table		*table;
}						t_philo;

typedef struct s_time
{
	time_t				tv_sec;
	suseconds_t			tv_usec;
}						t_time;

int				start_simulation(t_table *table);
void			*thd_rte(void *data);
t_table			*init_philosophers(int arc, char **argv);
void			init_forks(t_table *table);
int				ft_strcmp(const char *s1, const char *s2);
void			ft_mutex(t_philo *philo, pthread_mutex_t *philo_mutex);
long			time_micro(struct timeval start, struct timeval end);
void			ft_usleep(long usec, t_table *table);
int				safe_mutex(t_code_mtx code, t_mtx *mutex);
int				s_thd(t_c_th code, t_philo *p, void *(*th_r)(void *));
t_table			*safe_malloc(t_smalloc code, t_table *table);
long			gettime(t_time_val time_val);
void			firewatch(void *data, long time_start);
//void			printer(long time, int id, char *status, t_table *table);
void			all_stop_simulation(t_table *table);
long			el_st(long time_start);
int				all_eaten(t_table *table);
// PRINTER
int				error(char *msg);
void			fprinter_died(long time, int id, char *status, t_table *table);
void			fprinter_alive(long time, int id, char *status, t_table *table);
void			fprinter(long time, int id, char *status, t_table *table);
// UTILS
int				ft_atoi(const char *str);
void			ft_itoa(unsigned int n, char *str);
char			*reverse(char *str);
int				check_argv_positivity(char **argv);
int				ft_strlen(const char *str);
void			ft_free(t_table *table);
// MTX PHILO
unsigned int	m_id(t_philo *philo);
long			mtx_p_t_start(t_philo *philo);
int				m_stop_r(t_philo *philo);
void			mtx_stop_sim_write(t_philo *philo);
int				mtx_meal_eat_philo(t_philo *philo);
long			mtx_last_meal_time(t_philo *philo);
int				mtx_p_max_meals(t_philo *philo);
int				mtx_pnb_philo(t_philo *philo);
long			m_t_peat(t_philo *philo);
long			m_tdie(t_philo *philo);
// MTX TABLE
int				mtx_table_maxmeals(t_table *table);
int				mtx_tnb_philo(t_table *table);
long			mtx_table_tdie(t_table *table);
long			m_teat(t_table *table);
long			m_tsleep(t_table *table);
int				m_if_die_r(t_table *table);
void			m_die_w(t_table *table);

#endif