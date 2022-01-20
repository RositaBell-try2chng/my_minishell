#include "minishell.h"

void	ms_cmd_execute_exit(t_shell *shell)
{
	(void)shell;
	ft_putstr(COLOR_GREEN);
	ft_putstr("Exit: Vi pokinuli programmu. Prihodite eshe!!!\n");
	ft_putstr(COLOR_RESET);
}
