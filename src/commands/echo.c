#include "minishell.h"

void	ms_cmd_execute_echo(t_shell *shell)
{
		size_t	flg_n;
		size_t	i;
		size_t	j;

		i = 0;
		flg_n = ft_strcmp((shell->cmd->argv)[1], "-n") == 0;
		while (++i + flg_n < shell->cmd->argc)
		{
			j = 0;
			while ((shell->cmd->argv)[i + flg_n][j])
				j++;
			write(1, shell->cmd->argv[i + flg_n], j);
			write(1, " ", 1);
		}
		if (flg_n)
			write(1, "\n", 1);
		exit(0);
}