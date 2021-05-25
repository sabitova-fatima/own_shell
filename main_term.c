#include <term.h>
#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>

int		ft_strlen(char const *s)
{
	int		i;

	i = -1;
	while (*(s + ++i))
		;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	if (!(res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		++i;
	}
	j = 0;
	while (s2[j])
	{
		res[i + j] = s2[j];
		++j;
	}
	res[i + j] = '\0';
	return (res);
}

int	ft_putchar(char c)
{
	write(1, &c, 1);
    return (1);
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int main(int argc, char **argv, char **env)
{
    char *line;
    char str[2000];
    int l;
    struct termios term; // структура терминала
    char *term_name = "xterm-256color"; // env | grep TERM

    tcgetattr(0, &term); // получаем значения терминала
    term.c_lflag &= ~(ECHO); // пишем в них
    term.c_lflag &= ~(ICANON); // неканонич режим 
    tcsetattr(0, TCSANOW, &term); // записываем обратно в терм

    tgetent(0, term_name); // запуск термкапа (аналог - terminfo)

    // while (ft_strcmp(str, "\4"))
    // {
    //     tputs(save_cursor, 1, ft_putchar);
        while (ft_strcmp (str, "\n"))
        {
            l = read(0, str, 100);
            // str[l] = 0;
            // printf("\nstr: %s\n", str);
            if (!ft_strcmp(str, "\e[A"))
            {
                printf("previous\n");
            //     tputs(restore_cursor, 1, ft_putchar);
            //     tputs(tigetstr("ed"), 1, ft_putchar);
            //     write(1, "prev\n", 5);
            }
            else if (!ft_strcmp(str, "\e[B"))
            {
                printf("next\n");
            //     write(1, "next\n", 5);
            //     tputs(restore_cursor, 1, ft_putchar);
            //     tputs(tigetstr("ed"), 1, ft_putchar);
            }
            // else if (!ft_strcmp(str, key_backspace) && !ft_strcmp(str, "\177"))
            // {
            //     tputs(cursor_left, 1, ft_putchar);
            //     tputs(tigetstr("ed"), 1, ft_putchar);
            // }
            else
                write(1, str, l);
        // } while (ft_strcmp (str, "\n") && ft_strcmp(str, "\4"));
        // line = ft_strjoin(line, str);
        // printf("str : %s\n", line);
        }
        // write(1, "\n", 1);
    // }
}