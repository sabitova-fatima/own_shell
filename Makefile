NAME 		= minishell
SRCS 		= main.c get_next_line.c get_next_line_utils.c ft_split.c libft.c my_functions.c
CFLAGS 		= -Wall -Wextra -Werror -I. 
CC			= gcc
RM			= rm -rf

all:
		$(CC) $(SRCS) -o $(NAME)

clean:
		$(RM) $(OBJS)

fclean:	clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:	all clean fclean re bonus
