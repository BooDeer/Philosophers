/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boodeer <boodeer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 18:16:41 by boodeer           #+#    #+#             */
/*   Updated: 2021/10/30 23:52:41 by boodeer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo data;
	if (ac != 5 && ac != 6)
		return (error_message("Wrong number of arguments!", 1));
	if (check_data(av + 1))
		return (error_message("Invalid arguments!", 2));
	data = fill_data(av + 1, ac);
	print_philo(data);
	return (0);
}