#include "minishell.h"

void	ms_cmd_execute_cd(t_shell *shell)
{
	if (shell->cmd->argc == 1)
	{
		chdir(getenv("HOME"));
		ms_prompt_cwd(shell);
	}
	else if (shell->cmd->argc > 2)
	{
		ft_putstr(COLOR_RED);
		ft_putstr("cd: neobhodimo ukazat tolko odin parametr\n");
		ft_putstr(COLOR_RESET);
	}
	else
	{
		if (chdir(shell->cmd->argv[1]) != 0)
		{
			ft_putstr(COLOR_RED);
			ft_putstr("Error with ");
			ft_putstr(shell->cmd->argv[0]);
			ft_putstr(": ");
			perror(shell->cmd->argv[1]);
			ft_putstr(COLOR_RESET);
		}
		else
			ms_prompt_cwd(shell);
	}
}
