#include "minishell.h"

void	ms_cmd_execute_export(t_shell *shell)
{
	int		i;
	int 	j;
	char	**new_env;

	j = 0;
	ms_cmd_execute_unset(shell);
	while ((shell->envp)[j])
		j++;
	new_env = malloc(sizeof(char *) * (j + shell->cmd->argc));
	if (!new_env)
		return ;
	new_env[j + shell->cmd->argc] = NULL;
	while (--j >= 0)
		new_env[j] = (shell->envp)[j];
	i = 0;
	while (new_env && ++i < shell->cmd->argc)
	{
		new_env[j + i - 1] = ft_strdup((shell->cmd->argv)[i]);
		if (!new_env[j + i - 1])
			ft_arrayfree((void ***)(&new_env), j + i - 1);
	}
	if (new_env)
	{
		free(shell->envp);
		shell->envp = new_env;
	}
}