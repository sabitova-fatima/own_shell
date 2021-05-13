NAME 		= minishell
SRCS 		= main.c get_next_line.c get_next_line_utils.c ft_split.c
CFLAGS 		= -Wall -Wextra -Werror -I. 
CC			= gcc
RM			= rm -rf

all:	$(NAME)

$(NAME): 
		$(CC) $(SRCS) -o $(NAME)

clean:
		$(RM) $(OBJS)

fclean:	clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:	all clean fclean re bonus
