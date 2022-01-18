#include "minishell.h"

void	ms_cmd_execute_export(t_shell *shell)
{
	write(1, "do export\n", 10);
	exit(0);
}