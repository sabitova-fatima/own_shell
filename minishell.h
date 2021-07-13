#ifndef MINISHELL_H
# define MINISHELL_H
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# define BUFFER_SIZE 10

typedef struct s_global
{
	int	signal_worked;
	int	error_status;
	int	read_trouble;
	int	was_command;
	int	i;
}	t_global;

t_global	g_global;

typedef struct s_list
{
	int				fd;
	char			*ostatok;
	struct s_list	*next;
}	t_list;

typedef struct s_data
{
	int		fd_read;
	int		fd_write;
	int		was_redirect;
	int		type;
	char	*filename;
}	t_data;

typedef struct s_pipe
{
	int				fd_read;
	int				fd_write;
	int				fd[2];
	char			**command;
	char			*path;
	pid_t			pid;
	struct s_pipe	*prev;
	struct s_pipe	*next;
}	t_pipe;

// libft
void		ft_bzero(void *s, int n);
char		*ft_strnew(int size);
void		ft_putchar(char c);
void		ft_putstr(char const *s);
int			int_len(const char *str, char c);

//LIBFT2
int			ft_strcmp(char *s1, char *s2);
char		*ft_substr(char *s, int start, int len);

// my_functions
int			my_echo (char **command);
int			my_cd(char **command);
int			my_pwd(void);
char		**my_export (char **command, char **env, int *result);
int			print_sorted_env(char **env);

//MY_FUNCTIONS2
int			my_env(char **command, char **env);
int			my_exit (void);
void		write_error(t_data *data, char *filename);
char		*ft_empty(void);
void		total_free(char *input, char ***new, int ***fd);

// signals
void		ctrl_c(int signo);
void		ctrl_c_kid(int signo);
void		ctrl_slash(int signo);
void		ctrl_slash_kid(int signo);

// env
char		**copy_env(char **env);
int			env_len(char **env);
char		**realloc_env(int added, char **env_copy);
int			find_end_name(char *name);
void		print_str(char **env_copy);

//ENV_UTILS
int			where_to_put_env(char *name, char **env_copy);
char		*key_value(char *value);
char		**export_name_val(char *key, char *value, char **env_copy);
char		**my_unset(char **env, char **command, int *result);
char		**unset_env(int i_key, char **env);

//GNL
int			get_next_line(int fd, char **line);
int			clear(t_list **list, int fd, char *buf, int code);
t_list		*ft_lstnew(int content);
char		*ft_strchr(char *s, char c);
char		*ft_strdup(char *s, int len);
char		*ft_strjoin(char *s1, char *s2);

//BIG SPLIT
char		***super_split(char *s, char **env, int ****fd);
char		***split_3d(char **new, int ****fd_three);
void		cleaning_3d(char ***all, char **env, int ***fd);

//SPLIT
char		**ft_split(char *s, int *help);
int			count_spaces(char *s, char *c);
int			count_letters(char *s, char *c);
char		**ft_split2(char *s, int w_count, char *c, char **arr);
char		***split_spaces(char **arr, int ***fd_three);

//SPLITE PIPE
char		**ft_split_pipe(char *s, int p_count, char **arr);
int			count_pipe(char *s);
int			count_letters_pipe(char *s);
char		**split_pipes(char *s);

//CLEANER
char		*cleaner_semicolon_pipe_space(char *s);
int			into_quotes_cleaner(char *s, int j, char **new);
int			cleaner_other(char *s, char **new, char **env, int j);
void		cleaner(char **s, char **env, int ***fd);
int			main_cleaning(char *s, char **new, char **env, t_data *data);

//REDIRECT
void		next_redirect(char *s, char **env, t_data *data, char sign);
int			current_redirect(char *s, int j, char **env, t_data *data);
void		clean_filename(int i, t_data *data, char **new);
void		set_data(t_data *data, int ***fd, int i);
void		open_close(t_data *data, char *filename);

//PRE PARSER
int			check_empty_redirect(char **arr);
int			check_empty_commands(char **arr);
int			check_opened_quotes(char **array);
int			pre_parser(char *s);
int			into_check_empty_redirect(char *s, int j);

//PRE_CLEANER
int			pre_cleaner(char **s);
int			into_pre_cleaner(char *s, int j, int *quotes);
char		*join_char(char *s, char c);

//CLEANER_UTILS
char		*search_env(char *dollar, char **env);
int			ft_strncmp_env(char *s1, char *s2, int *j);
int			into_dollar(char *s, char **new, char **env, int j);
int			into_dollar2(char *s, int j, char **new, char **env);
int			ft_znak(int r);

//FREEDOMS
void		freedom_2d(char **arr);
void		freedom_3d(char ***arr);
void		freedom_2d_int(int **arr);
void		freedom_3d_int(int ***arr);

//UTILS
int			into_quotes(char *s, int i);
void		skip_spaces(char *line, int *i);
int			ft_strlen(char *s);
int			count_spaces_help(char *s, int i, int *w_count, char *c);
int			**create_2d(int help);

//UTILS2
int			ft_strncmp2(const char *s1, const char *s2, size_t n);
char		*ft_strdup2(char *s);
void		free_tmp(char **arr);
void		*freedom(char **johny, int w_count);
char		**iphone_pro(char const *s, int w_count, char c, char **johny);

//UTILS3
char		**ft_split3(char *s, char c);
void		ft_lstadd_back(t_pipe **pipes, t_pipe *new_pipe);
char		**own_function(t_pipe *tmp, char **env);
void		to_low(char *s);
int			ft_strncmp(char *s1, char *s2, int size);

//UTILS4
void		to_up(char *s);
void		heredoc(char *limiter);
char		*cleaner_help(char *new, t_data *data, char *s);
char		*init_empty(void);
char		*ft_itoa(int n);

//PIPES
char		**parse_pipes(char ***new, char **env, int ***fd, char *input);
int			if_bad_read(char **argv, int **fd);
int			is_one_command(t_pipe *pipes);
void		free_pipes(t_pipe *pipes);

//PIPE EXEC
char		**exec_one_command(t_pipe *tmp, char **env);
void		exec_cmds(t_pipe *pipes, char **env);
void		launch_process(t_pipe *tmp, char **env);
void		exec_child(t_pipe *pipes, char **env);
void		manage_fd(t_pipe *tmp, int *old_fd, int a);

//PIPE ARGV
void		parse_argv(char **argv, t_pipe *new_pipe, char **env, int **fd);
void		simple_init(char **argv, t_pipe *new_pipe, int **fd);
char		*absolut_path(char **env, char *command);
char		*check_path(char *command, char **env);
char		*check_path2(char **tmp, char *command);
#endif
