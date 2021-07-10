#include "minishell.h"

int	ft_strncmp2(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*one;
	unsigned char	*two;

	i = 0;
	one = (unsigned char *)s1;
	two = (unsigned char *)s2;
	while ((one[i] || two[i]) && i < n)
	{
		if (one[i] != two[i])
			return (one[i] - two[i]);
		i++;
	}
	return (0);
}

char	*ft_strdup2(char *s)
{
	int		i;
	char	*b;

	i = 0;
	b = (char *)malloc(sizeof(*s) * (ft_strlen(s) + 1));
	if (!b)
		return (NULL);
	while (s[i])
	{
		b[i] = s[i];
		i++;
	}
	b[i] = '\0';
	return (b);
}

void	free_tmp(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	*freedom(char **johny, int w_count)
{
	int	i;

	i = 0;
	while (i < w_count)
		free(johny[i++]);
	free(johny);
	return (NULL);
}

char	**iphone_pro(char const *s, int w_count, char c, char **johny)
{
	int		i;
	int		j;
	int		chari;

	i = -1;
	while (++i < w_count)
	{
		chari = 0;
		j = 0;
		while (*s == c)
			s++;
		while (s[chari] != c && s[chari] != '\0')
			chari++;
		johny[i] = (char *)malloc(sizeof(char) * (chari + 1));
		if (!johny[i])
			freedom(johny, i);
		while (j < chari)
			johny[i][j++] = *s++;
		johny[i][j] = '\0';
	}
	johny[i] = NULL;
	return (johny);
}
