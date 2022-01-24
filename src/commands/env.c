#include "minishell.h"

void	ms_cmd_execute_env(t_shell *shell)
{
	size_t	i;
	char	**env;

	i = -1;
	env = shell->envp;
	while (env[++i])
	{
		ft_putstr(env[i], 1);
		write(1, "\n", 1);
	}
	exit(0);
}

char	**envp_cpy(char **env, t_shell *shell)
{
	size_t	i;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		ft_puterror(shell, 2, "environment\n");
	shell->env_size = i + 1;
	new_env[i] = NULL;
	i = -1;
	while (new_env && env[++i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!(new_env[i]))
			ft_arrayfree((void ***)(&new_env), i);
	}
	return (new_env);
}