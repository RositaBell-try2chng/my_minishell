#include "minishell.h"

void	ms_tree_execute_cmd_hlp(t_shell *shell, bool async, bool p_i, bool p_o)
{
	if (shell->cmd == NULL)
		return ;
	shell->cmd->async = async;
	shell->cmd->stdin_pipe = p_i;
	shell->cmd->stdout_pipe = p_o;
}
