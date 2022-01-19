#include "minishell.h"

void	ms_cmd_execute_env(t_shell *shell)
{
	size_t	i;
	char	**env;

	i = -1;
	env = shell->envp;
	while (env[++i])
	{
		ft_putstr(env[i]);
		write(1, "\n", 1);
	}
	exit(0);
}