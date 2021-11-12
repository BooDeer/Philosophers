/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 18:16:41 by boodeer           #+#    #+#             */
/*   Updated: 2021/11/12 23:09:06 by hboudhir         ###   ########.fr       */
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

void	log_activity(int id, char *activity, pthread_mutex_t *quill)
{
	pthread_mutex_lock(quill);
	printf("%d %d %s\n", ft_curr_time(), id, activity);
	pthread_mutex_unlock(quill);
}
void	*routine_test(void *data)
{
	t_philo *philo = (t_philo *)data;

	int	i = 0;
	while (1)
	{
		pthread_mutex_lock(&philo->data->t_fork);
		pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
		log_activity(philo->id, PH_FORK, &QUILL_MTX);
		pthread_mutex_lock(&philo->data->forks[philo->id % philo->data->philo_nb]);
		pthread_mutex_unlock(&philo->data->t_fork);
		log_activity(philo->id, PH_FORK, &QUILL_MTX);
		log_activity(philo->id, PH_EAT, &QUILL_MTX);
		usleep(EAT_T);
		log_activity(philo->id, PH_SLEEP, &QUILL_MTX);
		usleep(SLEEP_T);
		log_activity(philo->id, PH_THINK, &QUILL_MTX);
		pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
		pthread_mutex_unlock(&philo->data->forks[philo->id % philo->data->philo_nb]);
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
	while (++i < end)
		philos[i].s_time = ft_curr_time();
}

void	start_simulation(t_data *data, t_philo *philos)
{
	struct timeval	tv;
	
	first_round_time(philos, data->philo_nb);
	for (int i = 0; i != data->philo_nb; i++)
		pthread_create(&(philos[i].p), NULL, &routine_test, &philos[i]);
}

int	supervisor(t_data *data, t_philo *philos)
{
	int	i;
	int	count;

	while (1)
	{
		
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
	supervisor(data, philos);
	for (int i = 0; i != data->philo_nb; i++)
	{
		pthread_join(philos[i].p, NULL);
		usleep(100);
	}
	return (0);
}