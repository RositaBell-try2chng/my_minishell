#include "minishell.h"

static void	ms_tree_execute_args(t_shell *shell, t_tree *node,
	t_tree *temp, int i)
{
	if (node == NULL || node->type != TREE_FILE)
	{
		shell->cmd->argc = 0;
		return ;
	}
	while (temp != NULL && (temp->type == TREE_ARG || temp->type == TREE_FILE))
	{
		temp = temp->right;
		i++;
	}
	shell->cmd->argv = (char **)malloc(sizeof(char *) * (i + 1));
	if (shell->cmd->argv == NULL)
		ft_puterror(shell, 2, "(massiv cmd->argv).\n");
	temp = node;
	i = 0;
	while (temp != NULL && (temp->type == TREE_ARG || temp->type == TREE_FILE))
	{
		shell->cmd->argv[i] = temp->value;
		temp = temp->right;
		i++;
	}
	shell->cmd->argv[i] = NULL;
	shell->cmd->argc = i;
}

static void	ms_cmd_execute(t_shell *shell)
{
	if (ft_strcmp(shell->cmd->argv[0], "cd") == 0 && shell->cmd->async == 0)
		return (ms_cmd_execute_cd(shell));
	if (ft_strcmp(shell->cmd->argv[0], "prompt") == 0 && shell->cmd->async == 0)
		return (ms_cmd_execute_prompt(shell));
	if (ft_strcmp(shell->cmd->argv[0], "exit") == 0 && shell->cmd->async == 0)
	{
		ms_cmd_execute_exit(shell);
		ms_cmd_argv_free(shell->cmd);
		ms_shell_destroy(shell);
		exit(0);
	}
	ms_cmd_execute_fork(shell);
}

static void	ms_tree_execute_simplecmd(t_shell *shell, t_tree *node,
	char *redirect_in, char *redirect_out)
{
	shell->cmd->redirect_in = redirect_in;
	shell->cmd->redirect_out = redirect_out;
	ms_tree_execute_args(shell, node, node, 0);
	if (MS_TEST_REGIME == 1)
		ms_cmd_print(shell->cmd);
	if (shell->cmd->argc > 0)
		ms_cmd_execute(shell);
	ms_cmd_argv_free(shell->cmd);
}

void	ms_tree_execute_cmd_hlp(t_shell *shell, bool async, bool p_i, bool p_o)
{
	if (shell->cmd == NULL)
		return ;
	shell->cmd->async = async;
	shell->cmd->stdin_pipe = p_i;
	shell->cmd->stdout_pipe = p_o;
}

void	ms_tree_execute_cmd(t_shell *shell, t_tree *node, int p_r, int p_w)
{
	if (shell->cmd == NULL || node == NULL)
		return ;
	shell->cmd->pipe_read = p_r;
	shell->cmd->pipe_write = p_w;
	if (node->type == TREE_REDIN)
		ms_tree_execute_simplecmd(shell, node->right, node->value, NULL);
	if (node->type == TREE_REDOUT)
		ms_tree_execute_simplecmd(shell, node->right, NULL, node->value);
	if (node->type == TREE_FILE)
		ms_tree_execute_simplecmd(shell, node, NULL, NULL);
}
