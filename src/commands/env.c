#include "minishell.h"

void	ms_cmd_execute_env(t_shell *shell)
{
	write(1, "do env\n", 7);
	exit(0);
}