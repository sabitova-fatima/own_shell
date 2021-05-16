#include "minishell.h"

int into_quotes(char *s, int i)
{
	char q;

	q = s[i++];
	while (s[i] && s[i] != q)
	{
		if (s[i] == '\\' && q == '"' &&
			(s[i+1] == '"' || s[i+1] == '\\'))
			i++;
		i++;
	}
	return (i);
}

int into_cleaner(char *s, int j, char **new, int *quotes)
{
	char q;

	while (s[j] != '"' && s[j] != '\'' && s[j])
	{
		if (s[j] == '\\' && s[j + 1])
			j++;
		*new = join_char(*new, s[j++]);
	}
	if (s[j] == '"' || s[j] == '\'')
	{
		(*quotes)++;
		q = s[j++];
		while (s[j] != q && s[j])
		{
			if (s[j] == '\\' && q == '"' &&
				(s[j+1] == '\\' || s[j+1] == '"'))
				j++;
			*new = join_char(*new, s[j++]);
		}
		if ((s[j] == '"' && q == '"') ||
			(s[j] == '\'' && q =='\''))
			(*quotes)--;
	}
	return (j);
}

int into_command_split(char *s, int *i, int w_count, char c)
{
	if (s[*i] != c && s[*i] != '"' && s[*i] != '\'' &&
	(s[(*i) + 1] == c || !s[(*i) + 1]))
		w_count++;
	else if (s[*i] == '\\' && s[(*i) + 1])
	{
		if (!s[(*i) + 2] || s[(*i) + 2] == ' ')
			w_count++;
		(*i)++;
	}
	else if (s[*i] == '"' || s[*i] == '\'')
	{
		*i = into_quotes(s, *i);
		if (s[(*i) + 1] == ' ' || !s[(*i) + 1])
			w_count++;
	}
	return (w_count);
}

int into_command_split2(char *s, int letter, char c)
{
	char q;

	if (s[letter] != '"' && s[letter] != '\'')
	{
		while (s[letter] != c && s[letter] && s[letter] != '"' &&
		s[letter] != '\'')
		{
			if (s[letter] == '\\' && s[letter + 1])
				letter++;
			letter++;
		}
	}
	if (s[letter] == '"' || s[letter] == '\'')
	{
		q = s[letter];
		letter = into_quotes(s, letter);
		if (s[letter] == q)
			letter++;
	}
	return (letter);
}

int into_command_semicolon(char *s, int i)
{
	while (s[++i] && s[i] != ';')
	{
		if (s[i] == '\\' && s[i + 1])
			i++;
		else if (s[i] == '\'' || s[i] == '"')
			i = into_quotes(s, i);
	}
	if (s[i] == ';')
		i++;
	return (i);
}

int w_count(char *s)
{
	int i;
	int count;

	i = -1;
	count = 0;
	while (s[++i])
	{
		if (s[i] == ';')
			count++;
		else if (s[i] && !s[i+1])
			count++;
		else if (s[i] == '\\' && s[i + 1])
		{
			if (!s[i + 2])
				count++;
			i++;
		}
		else if (s[i] == '\'' || s[i] == '"')
		{
			i = into_quotes(s, i);
			if (!s[i+1])
				count++;
		}
	}
	return (count);
}

static void	*freedom(char **arr, int count)
{
	int	i;

	i = 0;
	while (i < count)
		free(arr[i++]);
	free(arr);
	return (NULL);
}

char **split_semicolon(char *s, int count)
{
	char **arr;
	int i;
	int j;

	arr = (char**)malloc(sizeof(char *) * count + 1);
	if (!arr)
		return (NULL);
	i = -1;
	while (++i < count)
	{
		j = into_command_semicolon(s, -1);
		arr[i] = ft_strdup(s, j);
		if (!arr[i])
		{
			freedom(arr, i);
			return (NULL);
		}
		s += j;
	}
	arr[i] = NULL;
	return (arr);
}

void	skip_spaces(char *line, int *i)
{
	while (line[*i] == ' ' || (line[*i] >= 9 && line[*i] <= 13))
		(*i)++;
}

char ***split_spaces(char **arr, int count)
{
	char ***new;
	int i;

	new = (char ***)malloc(sizeof(char **) * count + 1);
	i = -1;
	while (++i < count)
	{
//		printf("before split |%s|\n", arr[i]);
		new[i] = ft_split(arr[i], ' ');
		if (!new[i])
			return (NULL);
	}
	new[i] = NULL;
	return (new);
}

int check_empty_commands(char **arr)
{
	int i;
	int j;

	i = -1;
	while(arr[++i])
	{
		j = 0;
		skip_spaces(arr[i], &j);
		if (arr[i][j] == ';')
			return (1);
	}
	return (0);
}

char *join_char(char *s, char c)
{
	char *tmp;
	char *new;

	tmp = s;
	new = ft_strjoin_char(s, c);
	if (ft_strlen(tmp))
		free(tmp);
	return (new);

}

char *cleaner_semicolon(char *s)
{
	int i;
	char *new;

	new = "";
	i = 0;
	while(s[i])
	{
		new = join_char(new, s[i]);
		i++;
	}
	i = 0;
	while(new[i])
		i++;
	if (new[i-1] == ';' && new[i-2] != '\\')
		new[i-1] = '\0';
	free(s);
	return (new);

}

int cleaner(char **s)
{
	int i = -1;
	int j;
	char *new;
	int quotes;

	while(s[++i])
	{
		new = "";
		quotes = 0;
		s[i] = cleaner_semicolon(s[i]);
		j = 0;
		skip_spaces(s[i], &j);
		while(s[i][j])
		{
			j = into_cleaner(s[i], j, &new, &quotes);
			j++;
		}
		if (quotes)
			return (1);
		free(s[i]);
		s[i] = new;
	}
	return (0);
}

char ***super_split(char *s)
{
	int count;
	char **array;
	char ***new;
	int i;
	int j;

	count = w_count(s);
//	printf("\n\n\ncommands_count = %d\n", count);
	array = split_semicolon(s, count);
	if (!array)
		return (NULL);
	if (check_empty_commands(array))
		return (NULL);
	new = split_spaces(array, count);

//	i = -1;
//	while (new[++i])
//	{
//		j = -1;
//		while (new[i][++j])
//			printf("i:%d  j:%d  before clear |%s|\n", i, j, new[i][j]);
//	}
	i = -1;
	while (new[++i])
	{
		if (cleaner(new[i]))
			return (NULL);
	}

	return (new);
}