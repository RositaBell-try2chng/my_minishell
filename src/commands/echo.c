#include "minishell.h"

static void	print_variable(char *s, char **env)
{
	size_t	i;
	size_t	j;
	char	flg;

	s++;
	i = 0;
	flg = 0;
	while (s[i])
		i++;
	while (!flg && *env)
	{
		while (*env && ft_strncmp(s, *env, i))
			env++;
		if (*env && (*env)[i + 1] == '=')
			flg = 1;
		else if (*env)
			env++;
	}
	if (!(*env))
		return;
	j = 0;
	while ((*env)[i + j + 1])
		j++;
	write(1, (*env + i + 1), j);
}

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
			if ((shell->cmd->argv)[i + flg_n][j] == '$')
				print_variable((shell->cmd->argv)[i + flg_n], shell->envp);
			else
			{
				while ((shell->cmd->argv)[i + flg_n][j])
					j++;
				write(1, shell->cmd->argv[i + flg_n], j);
				write(1, " ", 1);
			}
		}
		if (flg_n)
			write(1, "\n", 1);
		exit(0);
}