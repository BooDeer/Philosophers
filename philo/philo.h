/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 04:21:16 by hboudhir          #+#    #+#             */
/*   Updated: 2021/11/17 06:26:16 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_data
{
	int				philo_nb;
	int				t_td;
	int				t_te;
	int				t_ts;
	int				rds;
	int				s_point;
	pthread_mutex_t	*forks;
	pthread_mutex_t	quill;
	pthread_mutex_t	eat;
}			t_data;

typedef struct s_philo
{
	int			id;
	int			s_time;
	int			t_ate;
	pthread_t	p;
	t_data		*data;
}			t_philo;

int		error_message(char *error_str, int error_code);
void	print_philo(t_data *data);
int		ft_isdigit(int c);
int		ft_atoi(const char *c);
int		check_data(char **av);
t_data	*fill_data(char **data, int data_nb);
size_t	ft_strlen(const char *str);
int		ft_curr_time(void);
void	ft_usleep(long long sleep_time);
void	taking_forks(t_philo *philo);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	log_activity(int id, char *activity, pthread_mutex_t *quill,
			int s_time);
int		ft_curr_time(void);
size_t	ft_strlen(const char *str);
void	start_simulation(t_data *data, t_philo *philos);
void	*routine(void *data);
void	first_round_time(t_philo *philos, int end);
int		check_value(t_data *philo);
#endif