/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 18:16:41 by boodeer           #+#    #+#             */
/*   Updated: 2021/11/16 06:26:36 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		ft_curr_time(void)
{
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

size_t	ft_strlen(const char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	log_activity(int id, char *activity, pthread_mutex_t *quill, int s_time)
{
	pthread_mutex_lock(quill);
	printf("%d %d %s\n", ft_curr_time() - s_time, id, activity);
	pthread_mutex_unlock(quill);
}
void	*routine_test(void *data)
{
	t_philo *philo = (t_philo *)data;

	int	i = 0;
	while (1)
	{
		// pthread_mutex_lock(&philo->data->t_fork);
		// Locking the fork of [id - 1]
		pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
		// Output the log activity
		log_activity(philo->id, PH_FORK, &QUILL_MTX, S_TIME);
		// Locking the fork of [id % philo_nb] 
		pthread_mutex_lock(&philo->data->forks[philo->id % philo->data->philo_nb]);
		// pthread_mutex_unlock(&philo->data->t_fork);
		// Output the log activity
		log_activity(philo->id, PH_FORK, &QUILL_MTX, S_TIME);
		log_activity(philo->id, PH_EAT, &QUILL_MTX, S_TIME);
		philo->s_time = ft_curr_time();
		// Eating
		ft_usleep(EAT_T);
		// Incrementing the eating times
		philo->t_ate++;
		// Releasing the forks
		pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
		pthread_mutex_unlock(&philo->data->forks[philo->id % philo->data->philo_nb]);
		// Output the log activity
		log_activity(philo->id, PH_SLEEP, &QUILL_MTX, S_TIME);
		// Sleeping
		ft_usleep(SLEEP_T);
		// Thinking
		log_activity(philo->id, PH_THINK, &QUILL_MTX, S_TIME);
	}
	return (NULL);
}

/* */
t_philo *set_philos(t_data *data)
{
	t_philo *philo;
	int		i;

	i = -1;
	philo = (t_philo *)malloc(sizeof(t_philo) * data->philo_nb);
	while (++i < data->philo_nb)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i].s_time = -2;
		philo[i].t_ate = 0;
	}
	return (philo);
}


void	first_round_time(t_philo *philos, int end)
{
	int	i;

	i = -1;
	philos[0].data->s_point = ft_curr_time();
	while (++i < end)
		philos[i].s_time = ft_curr_time();
}

void	start_simulation(t_data *data, t_philo *philos)
{
	struct timeval	tv;
	int				i;

	i = 0;
	first_round_time(philos, data->philo_nb);
	while (i < data->philo_nb)
	{
		pthread_create(&(philos[i].p), NULL, &routine_test, &philos[i]);
		i += 2;
	}
	usleep(800);
	i = 1;
	while (i < data->philo_nb)
	{
		pthread_create(&(philos[i].p), NULL, &routine_test, &philos[i]);
		i += 2;
	}
	// for (int i = 0; i != data->philo_nb; i++)
		// pthread_create(&(philos[i].p), NULL, &routine_test, &philos[i]);
	
}

int	supervisor(t_data *data, t_philo *philos)
{
	int	i;
	int	count;

	while (1)
	{
		i = -1;
		count = 0;
		while (++i < data->philo_nb)
		{
			// if ((philos[i].s_time - ft_curr_time()) - data->t_td > 0)
			// printf("[Time to die]: %d\n",philos[i].s_time - ft_curr_time());
			if ( data->t_td - (ft_curr_time() - philos[i].s_time ) < 0)
			{
				printf("NIGGA: %d DIED because: %d passed\n",i + 1, (philos[i].s_time - data->s_point));
				return (2);
			}
			if (data->rds > 0 && philos[i].t_ate >= data->rds)
				count++;
			if (count >= data->philo_nb)
				return (1);
		}
		usleep(200);
	}
}

int	main(int ac, char **av)
{
	t_data *data;
	t_philo *philos;

	// parse the input data.
	// V V V V V V V V V V V V V V V V V V V V V V V

	if (ac != 5 && ac != 6)
		return (error_message("Wrong number of arguments!", 1));
	if (check_data(av + 1))
		return (error_message("Invalid arguments!", 2));
	
	// ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ 

	// fills a structure with the input data.
	data = fill_data(av + 1, ac);
	// print_philo(data);
	// allocate each philosopher and fills its data.
	philos = set_philos(data);
	// the threads loop
	start_simulation(data, philos);
	if (supervisor(data, philos))
		return (0);
	for (int i = 0; i != data->philo_nb; i++)
	{
		pthread_join(philos[i].p, NULL);
		usleep(100);
	}
	return (0);
}