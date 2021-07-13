#include "minishell.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	negativ;

	res = 0;
	negativ = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			negativ = -1;
		str++;
		if (*str == '+' || *str == '-')
			return (0);
	}
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = 10 * res + *str - '0';
		str++;
	}
	return (res * negativ);
}

char **env_with_shlvl(char **env)
{
	int 	shlvl;
	char	*shlvl_char;
	char 	*s;
	char 	**env_copy;
	int		pos;

	env_copy = copy_env(env);
	pos = where_to_put_env("SHLVL", env_copy);
	shlvl_char = ft_substr(env_copy[pos], 6, 3);
	shlvl = ft_atoi(shlvl_char);
	free(shlvl_char);
	shlvl_char = ft_itoa(shlvl + 1);
	s = ft_strjoin("SHLVL=", shlvl_char);
	free(env_copy[pos]);
	env_copy[pos] = s;
	free(shlvl_char);
	return (env_copy);
}

int	main(int argc, char **argv, char **env)
{
	char	***new;
	int		***fd;
	char	*input;
	char	**env_copy;

	(void)argc;
	(void)argv;

	g_global.error_status = 0;
	env_copy = env_with_shlvl(env);
	while (1)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, ctrl_slash);
		input = readline("e-bash> ");
		if (input == NULL)
			exit(0);
		new = super_split(input, env_copy, &fd);
		if (!new)
			free(input);
		if (!new)
			continue ;
		if (new[0][0])
			env_copy = parse_pipes(new, env_copy, fd, input);
		total_free(input, new, fd);
	}
}
