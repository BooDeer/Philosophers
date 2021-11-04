/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boodeer <boodeer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 18:16:41 by boodeer           #+#    #+#             */
/*   Updated: 2021/11/04 15:19:51 by boodeer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_test(void *data)
{
	t_philo *philo = (t_philo *)data;

	
	pthread_mutex_lock(&philo->data->quil);
	pthread_mutex_lock(philo->data->forks[philo->id - 1]);
	pthread_mutex_lock(philo->data->forks[philo->id % philo->data->philo_nb ]);
	pthread_mutex_unlock(&philo->data->quil);
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
		philo[i].l_ate = -1;
		philo[i].data = data;
	}
	return (philo);
}

int	main(int ac, char **av)
{
	t_data *data;
	t_philo *philos;

	if (ac != 5 && ac != 6)
		return (error_message("Wrong number of arguments!", 1));
	if (check_data(av + 1))
		return (error_message("Invalid arguments!", 2));
	data = fill_data(av + 1, ac);
	// print_philo(data);
	philos = set_philos(data);
	for (int i = 0; i != data->philo_nb; i++)
	{
		pthread_create(&philos[i].p, NULL, &routine_test, &philos[i]);
	}

	// pthread_join just to wait for all threads before exiting
	// to be deleted later.
	for (int i = 0; i != data->philo_nb; i++)
	{
		pthread_join(philos[i].p, NULL);
		usleep(100);
	}
	return (0);
}