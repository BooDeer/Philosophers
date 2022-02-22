/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 02:28:32 by hboudhir          #+#    #+#             */
/*   Updated: 2021/11/17 06:17:41 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_activity(int id, char *activity, pthread_mutex_t *quill, int s_time)
{
	pthread_mutex_lock(quill);
	printf("%d %d %s\n", ft_curr_time() - s_time, id, activity);
	pthread_mutex_unlock(quill);
}

void	ft_usleep(long long sleep_time)
{
	long long	start;

	start = ft_curr_time();
	usleep((sleep_time - 10) * 1000);
	while ((ft_curr_time() - sleep_time) < start)
		;
}

void	taking_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
	log_activity(philo->id, PH_FORK, &philo->data->quill,
		philo->data->s_point);
	pthread_mutex_lock(&philo->data->forks[philo->id
		% philo->data->philo_nb]);
	pthread_mutex_lock(&philo->data->eat);
	log_activity(philo->id, PH_FORK, &philo->data->quill,
		philo->data->s_point);
}

void	eating(t_philo *philo)
{
	log_activity(philo->id, PH_EAT, &philo->data->quill,
		philo->data->s_point);
	philo->s_time = ft_curr_time();
	pthread_mutex_unlock(&philo->data->eat);
	ft_usleep(philo->data->t_te);
	philo->t_ate++;
	pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
	pthread_mutex_unlock(&philo->data->forks[philo->id
		% philo->data->philo_nb]);
}

void	sleeping(t_philo *philo)
{
	log_activity(philo->id, PH_SLEEP, &philo->data->quill,
		philo->data->s_point);
	ft_usleep(philo->data->t_ts);
	log_activity(philo->id, PH_THINK, &philo->data->quill,
		philo->data->s_point);
}
