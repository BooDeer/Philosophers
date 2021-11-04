CC		= gcc -pthread
FLAGS	=
SRC		= philo.c utils_0.c
NAME	= philo

all: $(NAME)

$(NAME):
	@$(CC) $(FLAGS) $(SRC) -o $(NAME)

clean:
	@echo "Cleaning..."
fclean: clean
	@echo "Deleting program..."
	@rm -f philo
re: fclean all

.PHONY: clean fclean re