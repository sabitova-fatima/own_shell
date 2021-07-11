#include "minishell.h"

int	my_env(char **command, char **env)
{
	if (command[0] && !command[1])
		my_env_output(command, env);
	else if (command[1])
		ft_putstr("No arguments, please!\n");
	return (1);
}

int	my_exit (char **command)
{
	exit(0);
}
