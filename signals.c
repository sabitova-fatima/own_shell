//#include "minishell.h"
//
//void	ctrl_c(int signo)
//{
//	if (signo == SIGINT && global.signal_worked != 1)
//	{
//		global.signal_worked = 1;
//		global.error_status = 130;
//		ft_putstr("\ne-bash> ");
//		signal(SIGINT, ctrl_c);
//	}
//	global.signal_worked = 0;
//}
//
//void	ctrl_c_kid(int signo)
//{
//	if (signo == SIGINT && global.signal_worked != 11)
//	{
//		global.signal_worked = 11;
//		ft_putstr("\n");
//		global.error_status = 130;
//		signal(SIGINT, ctrl_c_kid);
//	}
//	global.signal_worked = 0;
//}
//
//void	ctrl_slash(int signo)
//{
//	if (signo == SIGQUIT && global.signal_worked != 2)
//	{
//		global.signal_worked = 2;
//		signal(SIGQUIT, ctrl_slash);
//
//	}
//	global.signal_worked = 0;
//}
//
//void	ctrl_slash_kid(int signo)
//{
//	if (signo == SIGQUIT && global.signal_worked != 22)
//	{
//		global.signal_worked = 22;
//    	ft_putstr("\n");
//		signal(SIGQUIT, ctrl_slash_kid);
//	}
//	global.signal_worked = 0;
//}
