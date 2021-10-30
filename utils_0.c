/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boodeer <boodeer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 20:44:29 by boodeer           #+#    #+#             */
/*   Updated: 2021/10/31 00:03:05 by boodeer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_message(char *error_str, int error_code)
{
	printf("%s%s%s\n",COLORS_RED, error_str, COLORS_DEFAULT);
	return (error_code);
}

void	print_philo(t_philo data)
{
	printf("%d\n", data.philo_nb);
	printf("%d\n", data.t_td);
	printf("%d\n", data.t_te);
	printf("%d\n", data.t_ts);
}

int		ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (c);
	return (0);
}

int		ft_atoi(const char *c)
{
	int		i;
	int		signe;
	long	res;

	i = 0;
	signe = 1;
	res = 0;
	while (c[i] && (c[i] == '\t' || c[i] == '\n' || c[i] == '\r' ||
		c[i] == '\v' || c[i] == '\f' || c[i] == ' '))
		i++;
	if (c[i] == '-')
		signe = -1;
	if (c[i] == '-' || c[i] == '+')
		i++;
	while (ft_isdigit(c[i]))
	{
		res = (res * 10) + (c[i] - '0');
		if ((res * signe) > 2147483647)
			return (-1);
		else if ((res * signe) < -2147483648)
			return (0);
		i++;
	}
	return ((int)(res * signe));
}

int		check_data(char **av)
{
	int		i;
	int		j;

	i = -1;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
			if (!ft_isdigit(av[i][j]))
				return (1);
	}
	return (0);
}

t_philo fill_data(char **data, int data_nb)
{
	t_philo philo;

	philo.philo_nb = ft_atoi(data[0]);
	philo.t_td = ft_atoi(data[1]);
	philo.t_te = ft_atoi(data[2]);
	philo.t_ts = ft_atoi(data[3]);
	if (data_nb == 6)
		philo.rds = ft_atoi(data[4]);
	return (philo);
}