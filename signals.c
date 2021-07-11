#include "minishell.h"

void	ctrl_c(int signo)
{
	if (signo == SIGINT && g_global.signal_worked != 1)
	{
		g_global.signal_worked = 1;
		g_global.error_status = 1;
		ft_putstr("\ne-bash> ");
		signal(SIGINT, ctrl_c);
	}
	g_global.signal_worked = 0;
}

void	ctrl_c_kid(int signo)
{
	if (signo == SIGINT && g_global.signal_worked != 11)
	{
		g_global.signal_worked = 11;
		ft_putstr("\n");
		g_global.error_status = 130;
		signal(SIGINT, ctrl_c_kid);
	}
	g_global.signal_worked = 0;
}

void	ctrl_slash(int signo)
{
	if (signo == SIGQUIT && g_global.signal_worked != 2)
	{
		g_global.signal_worked = 2;
		signal(SIGQUIT, ctrl_slash);
	}
	g_global.signal_worked = 0;
}

void	ctrl_slash_kid(int signo)
{
	if (signo == SIGQUIT && g_global.signal_worked != 22)
	{
		g_global.signal_worked = 22;
		ft_putstr("\n");
		signal(SIGQUIT, ctrl_slash_kid);
	}
	g_global.signal_worked = 0;
}
