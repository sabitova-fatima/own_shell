#include "minishell.h"

int error_status = 0;

char    **copy_env(char **env)
{
	int	i;
    char **env_copy;
    int len;
    int total_len;

    len = 0;
    i = 0;
    total_len = 0;
    while (env[len])
    {
        i = 0;
        while(env[len][i])
        {
            i++;
            total_len++;
        }
        len++;
    }
	env_copy = (char **)malloc(sizeof(char *) * (total_len + 1));
	i = -1;
	while (env[++i])
		env_copy[i] = ft_strdup(env[i], ft_strlen(env[i]));
    return(env_copy);
}

int main (int argc, char **argv, char **env)
{
	char    ***new;
    int     ***fd;
    char    *input;
    char    **env_copy;
    int     i;
    t_help  help;

	help.error = 0;
    env_copy = copy_env(env);
    while (1)
	{
        put_dirname();
        signal(SIGINT, ctrl_c);
        signal(SIGQUIT, ctrl_slash);
        input = readline(" \033[0m\033[33me-bash>\033[0m$ ");
        if (input == NULL)
            exit(0);
        new = super_split(input, env_copy, &fd, &help);
        if (new)
		{
			i = -1;
			while (new[++i])
            if (!start_own_function(new[i], env_copy, input))
                start_builtin(new[i] , ft_strsplit(find_path(env_copy), ':'), env_copy); // ПЕРЕПИСАТЬ
			if (!(input == NULL))
            	add_history(input);
        	help.error = 0;
		}
        else
        	help.error = 1;
	}
}
