#include "minishell.h"

char	**ft_split3(char *s, char c)
{
	char	**johny;
	int		w_count;
	int		i;

	i = 0;
	w_count = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			w_count++;
		i++;
	}
	johny = (char **)malloc(sizeof(char *) * (w_count + 1));
	if (!johny)
		return (NULL);
	johny = iphone_pro(s, w_count, c, johny);
	return (johny);
}

void	ft_lstadd_back(t_pipe **pipes, t_pipe *new_pipe)
{
	t_pipe	*temp;

	if (!new_pipe)
	{
		*pipes = NULL;
		return ;
	}
	if (!(*pipes))
		*pipes = new_pipe;
	else
	{
		temp = *pipes;
		while (temp->next)
			temp = temp->next;
		temp->next = new_pipe;
		new_pipe->prev = temp;
	}
}

char	**own_function(t_pipe *tmp, char **env)
{
	int	result;

	result = 0;
	if (!ft_strcmp("echo", tmp->command[0]))
		result = my_echo(tmp->command);
	if (!ft_strcmp("pwd", tmp->command[0]))
		result = my_pwd();
	if (!ft_strcmp("env", tmp->command[0]))
		result = my_env(tmp->command, env);
	if (!ft_strcmp("cd", tmp->command[0]))
		result = my_cd(tmp->command);
	if (!ft_strcmp("exit", tmp->command[0]))
		result = my_exit(tmp->command);
	if (!ft_strcmp("export", tmp->command[0]))
		env = my_export(tmp->command, env, &result);
	if (!ft_strcmp("unset", tmp->command[0]))
		env = my_unset(env, tmp->command, &result);
	if (result == 0)
		return (NULL);
	return (env);
}

void	to_low(char *s)
{
	int	i;

	if (!s)
		return ;
	i = -1;
	while (s[++i])
	{
		if (s[i] >= 'A' && s[i] <= 'Z')
			s[i] += 32;
	}
}

int	ft_strncmp(char *s1, char *s2, int size)
{
	unsigned int	i;

	if (size == 0)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && s2[i] != '\0' && i < size - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	if (i != size)
		return (s1[i] - s2[i]);
	return (0);
}
