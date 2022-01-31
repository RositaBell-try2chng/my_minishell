#include "minishell.h"

void	ms_cmd_execute_echo(t_shell *shell)
{
	size_t	flg_n;
	size_t	i;
	size_t	j;

	i = 0;
	if (shell->cmd->argc < 2)
		return ;
	flg_n = ft_strcmp((shell->cmd->argv)[1], "-n") == 0;
	while (++i + flg_n < (size_t)shell->cmd->argc)
	{
		j = 0;
		while ((shell->cmd->argv)[i + flg_n][j])
			j++;
		write(1, shell->cmd->argv[i + flg_n], j);
		if (i + flg_n + 1 < (size_t)shell->cmd->argc)
			write(1, " ", 1);
	}
	if (!flg_n)
		write(1, "\n", 1);
	ms_cmd_argv_free(shell->cmd);
	ms_shell_destroy(shell);
	exit(0);
}