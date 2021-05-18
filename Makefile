NAME 		= minishell
SRCS 		= main.c get_next_line.c get_next_line_utils.c ft_split.c \
			libft.c my_functions.c env_key.c \
			big_split.c cleaner.c env.c pre_parser.c split_pipe.c split.c \
			utils.c utils2.c utils3.c utils4.c
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
