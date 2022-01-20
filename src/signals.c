#include "minishell.h"

//Реакция на нажатие Ctrl-"C", Ctrl-"Z" и Ctrl-"\"
static void	ms_signal_handler(int sigtype)
{
	if (sigtype == SIGINT && MS_TEST_REGIME == 1)
		ft_putstr("\nVi nazhali \"Ctrl+C\"\n", 1);
	if (sigtype == SIGTSTP && MS_TEST_REGIME == 1)
		ft_putstr("\nVi nazhali \"Ctrl+Z\"\n", 1);
	if (sigtype == SIGQUIT && MS_TEST_REGIME == 1)
		ft_putstr("\nVi nazhali \"Ctrl+\\\"\n", 1);
	if (sigtype == SIGINT || sigtype == SIGTSTP || sigtype == SIGQUIT)
	{
		if (MS_TEST_REGIME == 0)
			ft_putstr("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

//Игнорирование сигналов Ctrl-"C", Ctrl-"Z" и Ctrl-"\"
void	ms_ignore_signals(t_shell *shell)
{
	shell->sigset = true;
	shell->sigint_fun = signal(SIGINT, ms_signal_handler);
	signal(SIGTSTP, ms_signal_handler);
	signal(SIGQUIT, ms_signal_handler);
}

// Восстановление сигнала "Ctrl-C" в дочернем процессе
void	ms_sigint_in_child(t_shell *shell)
{
	if (shell->sigset == true)
	{
		signal(SIGINT, shell->sigint_fun);
	}
}
