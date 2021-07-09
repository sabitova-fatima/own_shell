#include "minishell.h"

void	ctrl_c(int signo)
{
	if (signo == SIGINT && signal_worked != 1)
	{
		signal_worked = 1;
		error_status = 130;
		ft_putstr("\n");
		put_dirname();
        ft_putstr(" \033[0m\033[33me-bash>\033[0m$ ");
		signal(SIGINT, ctrl_c);
	}
		// printf("signal_status %d\n", signal_worked);

}

void	ctrl_c_kid(int signo)
{
	
	if (signo == SIGINT && signal_worked != 11)
	{
		signal_worked = 11;
		ft_putstr("\n");
		error_status = 130;
		signal(SIGINT, ctrl_c_kid);
	}
		// printf("signal_status %d\n", signal_worked);

}

void	ctrl_slash(int signo)
{
	if (signo == SIGQUIT && signal_worked != 2)
	{
		signal_worked = 2;
		signal(SIGQUIT, ctrl_slash);

	}
		// printf("signal_status %d\n", signal_worked);

}

void	ctrl_slash_kid(int signo)
{
	if (signo == SIGQUIT && signal_worked != 22)
	{
		signal_worked = 22;
    	ft_putstr("\n");
		signal(SIGQUIT, ctrl_slash_kid);
	}
		// printf("signal_status %d\n", signal_worked);

}
