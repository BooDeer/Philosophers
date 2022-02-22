/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 06:15:53 by hboudhir          #+#    #+#             */
/*   Updated: 2021/11/20 02:41:54 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_curr_time(void)
{
	struct timeval	tv;

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

void	start_simulation(t_data *data, t_philo *philos)
{
	int				i;

	i = 0;
	first_round_time(philos, data->philo_nb);
	while (i < data->philo_nb)
	{
		pthread_create(&(philos[i].p), NULL, &routine, &philos[i]);
		i += 2;
	}
	ft_usleep(20);
	i = 1;
	while (i < data->philo_nb)
	{
		pthread_create(&(philos[i].p), NULL, &routine, &philos[i]);
		i += 2;
	}
}

int	check_value(t_data *philo)
{
	if (philo->philo_nb < 0 || philo->t_td < 0 || philo->t_te < 0
		|| philo->t_ts < 0)
		return (1);
	return (0);
}
