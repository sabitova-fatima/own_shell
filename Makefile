NAME 		= minishell
SRCS 		= main.c \
			libft.c \
			my_functions.c  \
			big_split.c \
			cleaner.c \
			cleaner_utils.c \
			freedoms.c \
			get_next_line.c \
			get_next_line_utils.c \
			pre_cleaner.c \
			pre_parser.c \
			redirect.c \
			split.c \
			split_pipe.c \
			split_pre.c \
			split_semi.c \
			utils.c \
			utils2.c \
			signals.c \
			env.c \
			pipes.c
			
CFLAGS 		= -Wall -Wextra -Werror -I. 
CC			= gcc
RM			= rm -rf

all:
		$(CC) -ltermcap -L/usr/include -lreadline $(SRCS) -o $(NAME)

clean:
		$(RM) $(OBJS)

fclean:	clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:	all clean fclean re bonus
