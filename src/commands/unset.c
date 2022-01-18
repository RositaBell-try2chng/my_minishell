#include "minishell.h"

void	ms_cmd_execute_unset(t_shell *shell)
{
	write(1, "do unset\n", 9);
	exit(0);
}