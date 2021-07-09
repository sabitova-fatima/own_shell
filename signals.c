#include "minishell.h"

void	ctrl_c(int signo)
{
	if (signo == SIGINT)
	{
		error_status = 130;
		ft_putstr("\n");
		put_dirname();
        ft_putstr(" \033[0m\033[33me-bash>\033[0m$ ");
		signal(SIGINT, ctrl_c);
	}
}

void	ctrl_c_kid(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr("\n");
		error_status = 130;
		// signal(SIGINT, ctrl_c_kid);
	}
}

void	ctrl_slash(int signo)
{
	if (signo == SIGQUIT)
		signal(SIGQUIT, ctrl_slash);
}

void	ctrl_slash_kid(int signo)
{
	if (signo == SIGQUIT)
	{
    	ft_putstr("\n");
		// signal(SIGQUIT, ctrl_slash_kid);
	}
}
