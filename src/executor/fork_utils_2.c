#include "minishell.h"

static char	*check_cmd(const char *cmd, size_t s_cmd, char *path, size_t s_path)
{
	char	*new;
	size_t	i;
	int		flg;

	flg = s_path != 0;
	i = -1;
	new = malloc(sizeof(char) * (s_cmd + s_path + 1 + flg));
	if (!new)
		return (NULL);
	while (++i < s_path)
		new[i] = path[i];
	if (flg)
		new[s_path] = '/';
	i = -1;
	while (++i < s_cmd)
		new[i + s_path + flg] = cmd[i];
	new[i + s_path + flg] = 0;
	if (!access(new, X_OK))
		return (new);
	free(new);
	return (NULL);
}

static char	parse_cmd(char **dst, const char *cmd, char *path)
{
	size_t	size_cmd;
	size_t	size_path;

	size_cmd = 0;
	while (cmd[size_cmd])
		size_cmd++;
	*dst = check_cmd(cmd, size_cmd, path, 0);
	if (*dst)
		return (0);
	while (*path)
	{
		size_path = 0;
		while (path[size_path] && path[size_path] != ':')
			size_path++;
		*dst = check_cmd(cmd, size_cmd, path, size_path);
		if (*dst)
			return (0);
		path += size_path + 1;
	}
	return (1);
}


void	do_shell_command(t_shell *shell)
{
	size_t	i;
	char	*path;

	i = 0;
	while (shell->envp[i] && ft_strncmp("PATH=", shell->envp[i], 5) != 0)
		i++;
	if (shell->envp[i])
		path = (shell->envp[i]) + 5;
	else
		path = "/bin:/usr/bin";
	if (parse_cmd(&((shell->cmd->argv)[0]), (shell->cmd->argv)[0], path))
	{
		ft_putstr("Command doesn't exist(", 2);
		ft_putstr((shell->cmd->argv)[0], 2);
		write(2, ").\n", 3);
	}
	execve(shell->cmd->argv[0], shell->cmd->argv, shell->envp);
	ft_puterror(shell, 3, "");
	ms_cmd_argv_free(shell->cmd);
	ms_shell_destroy(shell);
	exit(1);
}