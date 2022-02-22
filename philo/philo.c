/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 18:16:41 by boodeer           #+#    #+#             */
/*   Updated: 2021/11/17 06:19:37 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *data)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)data;
	i = 0;
	while (1)
	{
		taking_forks(philo);
		eating(philo);
		sleeping(philo);
	}
	return (NULL);
}

t_philo	*set_philos(t_data *data)
{
	t_philo	*philo;
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
		philos[i].s_time = philos[0].data->s_point;
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
			if (!pthread_mutex_lock(&data->eat) && data->t_td
				- (ft_curr_time() - philos[i].s_time) < 0)
			{
				pthread_mutex_lock(&data->quill);
				printf("%d %d %s\n", ft_curr_time() - philos[i].s_time,
					i + 1, PH_DIE);
				return (2);
			}
			pthread_mutex_unlock(&data->eat);
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
	t_data	*data;
	t_philo	*philos;

	if (ac != 5 && ac != 6)
		return (error_message("Wrong number of arguments!", 1));
	if (check_data(av + 1))
		return (error_message("Invalid arguments!", 2));
	data = fill_data(av + 1, ac);
	if (!data)
		return (1);
	philos = set_philos(data);
	start_simulation(data, philos);
	if (supervisor(data, philos))
		return (0);
	return (0);
}
