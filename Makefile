SRC 		= main.c \
			libft.c \
			libft2.c \
			my_functions.c  \
			my_functions2.c  \
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
			split_semi.c \
			utils.c \
			utils2.c \
			utils3.c \
			utils4.c \
			signals.c \
			env.c \
			env_utils.c \
			pipes.c \
			pipe_argv.c \
			pipe_exec.c

OBJ = 		$(SRC:.c=.o)
NAME 		= minishell
CFLAGS 		= -Wall -Wextra -Werror -I.
CC			= gcc
RM			= rm -rf

%.o: %.c
	$(CC) $(CFLAGS) -c $<

all: $(NAME)
$(NAME): $(OBJ)
		$(CC) $(CFLAGS) -L/Users/khouten/.brew/opt/readline/lib -I/Users/khouten/.brew/opt/readline/include -lreadline $(SRC) -o $(NAME)
clean:
		$(RM) $(OBJ)
fclean:	clean
		$(RM) $(NAME)
re:		fclean all

.PHONY:	all clean fclean re bonus