#include "minishell.h"

int	find_variable(char **env, char *s)
{
	size_t	i;
	int		res;
	char	flg;

	i = 0;
	flg = 0;
	res = 0;
	while (s[i] != '=' && s[i])
		i++;
	while (!flg && env[res])
	{
		while (env[res] && ft_strncmp(s, env[res], i))
			res++;
		if (env[res] && env[res][i] == '=')
			flg = 1;
		else if (env[res])
			res++;
	}
	if (!env[res])
		return (-1);
	return (res);
}

static void	delete_variable(char **env)
{
	char	*tmp;
	size_t	i;

	tmp = *env;
	i = -1;
	while (env[++i])
		env[i] = env[i + 1];
	free(tmp);
}

void	ms_cmd_execute_unset(t_shell *shell)
{
	int	i;
	int j;

	i = 0;
	while (++i < shell->cmd->argc)
	{
		j = find_variable(shell->envp, (shell->cmd->argv)[i]);
		if (j > 0)
			delete_variable(shell->envp + j);
	}
}