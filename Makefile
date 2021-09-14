NAME = philo

MANDATORY	=	main.c\
				src/ft_utils.c\
				src/error.c\
				src/routine.c\
				src/mutex.c\
				src/mutex_2.c


OBJ = $(MANDATORY:.c=.o)

CC = gcc

INC_1 = -I./includes

FLAGS	= -Wall -Wextra -Werror

SANITIZE	=-fsanitize=address -g3

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(FLAGS) $(INC_1) $(MANDATORY) $(SANITIZE) -lpthread  -o $(NAME)

clean:
	rm -rf *.o
	rm -rf a.out
	rm -rf a.out*

fclean: clean
	rm -rf $(NAME)
	rm -rf $(NAME).dSYM
	rm -rf *.a

re: fclean all

.PHONY:	all clean fclean bonus re
