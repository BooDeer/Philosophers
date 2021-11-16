/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 02:28:32 by hboudhir          #+#    #+#             */
/*   Updated: 2021/11/14 03:54:04 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long long sleep_time)
{
	long long start;

    start = ft_curr_time();
    usleep((sleep_time - 10) * 1000);
    while((ft_curr_time() - sleep_time) < start)
        ;
}