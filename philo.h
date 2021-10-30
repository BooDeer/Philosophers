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


typedef	struct s_philo
{
	int	philo_nb;
	int	t_td;
	int	t_te;
	int	t_ts;
	int	rds;
}			t_philo;

int	error_message(char *error_str, int error_code);
void	print_philo(t_philo data);
int		ft_isdigit(int c);
int		ft_atoi(const char *c);
int		check_data(char **av);
t_philo fill_data(char **data, int data_nb);


#endif