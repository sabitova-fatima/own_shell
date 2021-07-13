#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	***new;
	int		***fd;
	char	*input;
	char	**env_copy;

	(void)argc;
	(void)argv;
	env_copy = copy_env(env);
	g_global.error_status = 0;
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
