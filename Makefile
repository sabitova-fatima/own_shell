NAME 		= minishell
SRC 		= big_split.c \
			cleaner.c \
			get_next_line.c \
			get_next_line_utils.c \
			main_khouten.c \
			pre_cleaner.c \
			pre_parser.c \
			split.c \
			split_pipe.c \
			split_pre.c \
			split_semi.c \
			utils.c \
			utils2.c \
			utils3.c \
			utils4.c

#OBJ = $(SRC:.c=.o)

#CFLAGS 		=  -Wall -Wextra -Werror
CC			= gcc
RM			= rm -rf

all:
		$(CC) $(SRC) -o $(NAME) -g && ./$(NAME)
val:
		$(CC) $(SRC) -o $(NAME) -g && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)
clean:
		$(RM) $(NAME)
#re:		clean all

.PHONY:	all clean  re


