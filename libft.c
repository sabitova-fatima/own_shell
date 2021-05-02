# include <unistd.h>

void	ft_bzero(void *s, int n)
{
	char	*ptr;
	int	i;

	if (!n)
		return ;
	ptr = s;
	i = 0;
	while (i < n)
		*(ptr + i++) = 0;
}

char	*ft_strnew(int size)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	ft_bzero(str, size + 1);
	return (str);
}

int		ft_strlen(const char *s)
{
	int		i;

	i = -1;
	while (*(s + ++i))
		;
	return (i);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char const *s)
{
	int i;

	i = 0;
	while(s[i] != '\0')
	{	
		ft_putchar(s[i]);
		i++;
	}
}

static int	int_len(const char *str, char c)
{
	int word;

	word = 0;
	if (*str != c && *str)
	{
		str++;
		word++;
	}
	while (*str)
	{
		while (*str == c)
		{
			str++;
			if (*str != c && *str)
				word++;
		}
		str++;
	}
	return (word);
}

static int		ft_ln(const char *str, char c)
{
	int count;

	count = 0;
	while (*str != c && *str)
	{
		count++;
		str++;
	}
	return (count);
}

char	**ft_strsplit(char const *s, char c)
{
	int		j;
	int		i;
	char	**spt;

	j = 0;
	i = 0;
	if (!s || (!(spt = (char **)malloc(sizeof(char *) * (int_len(s, c) + 1)))))
		return (NULL);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s != c && *s)
		{
			if (!(spt[j] = (char *)malloc(sizeof(char) * (ft_ln(s, c) + 1))))
				return (NULL);
			while (*s && *s != c)
				spt[j][i++] = (char)*s++;
			spt[j][i] = '\0';
			j++;
			i = 0;
		}
	}
	spt[j] = NULL;
	return (spt);
}

char	*ft_strdup(const char *s1)
{
	int	len;
	char	*str;
	char	*tmp;

	len = ft_strlen(s1);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (str == NULL)
		return (NULL);
	tmp = str;
	while (len--)
		*str++ = *s1++;
	*str = '\0';
	return (tmp);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	int	i;
	int	j;
	int	s1_len;
	int	s2_len;

	if (!s1)
		return (NULL);
	if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_str = ft_strnew(s1_len + s2_len + 1);
	if (!new_str)
		return (NULL);
	i = -1;
	j = -1;
	while (++i < s1_len)
		*(new_str + i) = *(s1 + i);
	while (++j < s2_len)
		*(new_str + i++) = *(s2 + j);
	return (new_str);
}


// int ft_strcmp(const char *s1, const char *s2)
// {
// 	int   i;
// 	unsigned char *one;
// 	unsigned char *two;
	
// 	i = 0;
	
// 	if (!s1 || !s2)
// 		return (-1);

// 	one = (unsigned char *)s1;
// 	two = (unsigned char *)s2;
	
// 	while ((one[i] || two[i]))
// 	{
// 		if (one[i] != two[i]);
// 		return (one[i] - two[i]);
// 		i++;
// 	}
// 	return (0);
// }

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}