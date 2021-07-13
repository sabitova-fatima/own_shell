#include "minishell.h"

void    ctrl_c(int signo)
{
	if (signo == SIGINT && g_global.signal_worked != 1)
	{
		g_global.signal_worked = 1;
		g_global.error_status = 1;
		rl_on_new_line();
		rl_redisplay();
		write (1, "\n", 1);
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
	}
	g_global.signal_worked = 0;
}
void    ctrl_c_kid(int signo)
{
	if (signo == SIGINT && g_global.signal_worked != 11)
	{
		g_global.signal_worked = 11;
		g_global.error_status = 130;
//		signal(SIGINT, ctrl_c_kid);
	}
	 g_global.signal_worked = 0;
}
void    ctrl_slash(int signo)
{
	if (signo == SIGQUIT && g_global.signal_worked != 2)
	{
		rl_on_new_line();
		rl_redisplay();
		g_global.signal_worked = 2;
		signal(SIGQUIT, ctrl_slash);
	}
	g_global.signal_worked = 0;
}
void    ctrl_slash_kid(int signo)
{
	if (signo == SIGQUIT)
	{
		ft_putstr("\n");
		g_global.signal_worked = 22;
		signal(SIGQUIT, ctrl_slash_kid);
	}
	g_global.signal_worked = 0;
}