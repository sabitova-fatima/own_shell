//#include "minishell.h"
//
//char *env_key(char *s)
//{
//	int i;
//	int j;
//	char *new_var;
//
//	i = -1;
//	while(s[++i] && s[i] != '=')
//	{
//		if (!((s[0] >= 'A' && s[0] <= 'Z') || s[0] == '_'))
//			return (NULL);
//		if (!((s[i] >= '0' && s[i] <= '9') || (s[i] >= 'A' && s[i] <= 'Z') ||
//			  s[i] == '_'))
//			return (NULL);
//	}
//	new_var = (char *)malloc(sizeof(char) * i + 1);
//	if (!new_var)
//		return (NULL);
//	j = -1;
//	while (++j < i)
//		new_var[j] = s[j];
//	new_var[j] = '\0';
//	return (new_var);
//}
//
//char *env_value(char *s)
//{
//	int i;
//
//	i = 0;
//	while(s[i] && s[i] != '=')
//		i++;
//	return (s + (++i));
//}