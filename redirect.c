#include "minishell.h"

void next_redirect(char *s, char **env, int *help_var, char sign)
{
	int j;
	char *filename;

	help_var[3] = (int)sign;
	if (sign == 5)
		help_var[3] = 63;
//	printf("NEXT SIGN %d\n", help_var[3]);
	j = 0;
	skip_spaces(s, &j);
	filename = (char *)malloc(1);
	filename[0] = '\0';
	while(s[j] && s[j] != '>' && s[j] != '<')
		j = cleaner_other(s, j, &filename, env);
	open_close(help_var, filename);
//	printf("next redir [%s]\n", filename);
//	printf("read: %d write:%d\n", help_var[0], help_var[1]);
	free(filename);
	help_var[2] = 1;
}

int current_redirect(char *s, int j, char **env, int *help_var)
{
	char *filename;

	while(s[j])
	{
		if ((s[j - 1] == '>' || s[j - 1] == '<') && s[j] != '>')
			help_var[3] = (int)s[j - 1];
		if (s[j - 1] == '>' && s[j] == '>')
			help_var[3] = (int)(s[j++] + 1);
//		printf("SIGN %d\n", help_var[3]);
		if (!s[j])
			break;
		filename = (char *)malloc(1);
		filename[0] = '\0';
		while(s[j] && s[j] != '>' && s[j] != '<')
			j = cleaner_other(s, j, &filename, env);
		open_close(help_var, filename);
//		printf("redir [%s]\n", filename);
//		printf("read: %d write:%d\n", help_var[0], help_var[1]);
		free(filename);
		if (!s[j++])
			break;
	}
	return (j - 1);
}

void clean_filename(int i, int *help_var, char **new)
{
	if (i == 0)
		return ;
	if (!help_var[2])
		return ;
	free(*new);
	*new = (char *)malloc(1);
	*new[0] = '\0';
	help_var[2] = 0;
}

void set_helpvar(int *help_var, int *****fd, int i, int *w_h)
{
	//[0] = fd read
	//[1] = fd write
	//[2] = was_redirect
	//[3] = sign

	if (i == -1)
	{
		help_var[0] = -5;
		help_var[1] = -5;
		help_var[2] = 0;
		help_var[3] = 0;
	}
	else
	{
		if (help_var[0] != -5)
		{
			(*fd)[w_h[0]][w_h[1]][i - 1][0] = help_var[0];
			printf("final fd read %d\n", (*fd)[w_h[0]][w_h[1]][i - 1][0]);
		}
		if (help_var[1] != -5)
		{
			(*fd)[w_h[0]][w_h[1]][i - 1][1] = help_var[1];
			printf("final fd write %d\n", (*fd)[w_h[0]][w_h[1]][i - 1][1]);
		}
	}
}

void open_close(int *help_var, char *filename)
{
	if (help_var[3] == (int)'>')
	{
		if (help_var[1] != -5)
			close(help_var[1]);
		help_var[1] = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0666);
	}

	if (help_var[3] == (int)'<')
	{
		if (help_var[0] != -5)
			close(help_var[0]);
		help_var[0] = open(filename, O_RDONLY, 0666);

	}
	if (help_var[3] == (int)('>' + 1))
	{
		if (help_var[1] != -5)
			close(help_var[1]);
		help_var[1] = open(filename, O_RDWR | O_CREAT | O_APPEND, 0666);
	}
}