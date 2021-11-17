#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>



# define COLORS_DEFAULT "\033[0;0m"
# define COLORS_RED "\033[031m"

/* States of philosopher  */
# define PH_EAT "is eating"
# define PH_FORK "has taken a fork"
# define PH_SLEEP "is sleeping"
# define PH_THINK "is thinking"
# define PH_DIE "died"
# define EAT_T philo->data->t_te
# define SLEEP_T philo->data->t_ts
# define QUILL_MTX philo->data->quill
# define S_TIME philo->data->s_point
typedef	struct s_data
{
	int	philo_nb;
	int	t_td; // time to die
	int	t_te; // time to eat
	int	t_ts; // time to sleep
	int	rds; // number of time to eat
	int	s_point; // initial date (To be substracted)
	pthread_mutex_t *forks;
	pthread_mutex_t quill;
	pthread_mutex_t eat;
}			t_data;

typedef struct s_philo
{
	int	id; // philo id (1-[Number of philos])
	int	s_time; // start_time (start of the simulation / time last startd eating)
	int	t_ate; // (how many times the philosopher ate)
	pthread_t p;
	t_data *data;
}			t_philo;

int	error_message(char *error_str, int error_code);
void	print_philo(t_data *data);
int		ft_isdigit(int c);
int		ft_atoi(const char *c);
int		check_data(char **av);
t_data *fill_data(char **data, int data_nb);
size_t	ft_strlen(const char *str);
int		ft_curr_time(void);
void	ft_usleep(long long sleep_time);

#endif