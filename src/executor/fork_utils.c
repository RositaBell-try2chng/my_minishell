#include "minishell.h"

void	ms_cmd_execute_fork_error(void)
{
	ft_putstr(COLOR_RED);
	perror("Error with fork()");
	ft_putstr(COLOR_RESET);
}

void	ms_cmd_execute_fd_null(t_shell *shell)
{
	int	fd;

	fd = open("/dev/null", O_RDWR);
	if (fd == -1)
	{
		ft_putstr(COLOR_RED);
		perror("Error with /dev/null");
		ft_putstr(COLOR_RESET);
		ms_cmd_argv_free(shell->cmd);
		ms_shell_destroy(shell);
		exit(1);
	}
	dup2(fd, 0);
}

void	ms_cmd_execute_fd_redirect_in(t_shell *shell)
{
	int	fd;

	fd = open(shell->cmd->redirect_in, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr(COLOR_RED);
		ft_putstr("Error with ");
		perror(shell->cmd->redirect_in);
		ft_putstr(COLOR_RESET);
		ms_cmd_argv_free(shell->cmd);
		ms_shell_destroy(shell);
		exit(1);
	}
	dup2(fd, 0);
}

void	ms_cmd_execute_fd_redirect_out(t_shell *shell)
{
	int	fd;

	fd = open(shell->cmd->redirect_out, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR
			| S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
	{
		ft_putstr(COLOR_RED);
		ft_putstr("Error with ");
		perror(shell->cmd->redirect_out);
		ft_putstr(COLOR_RESET);
		ms_cmd_argv_free(shell->cmd);
		ms_shell_destroy(shell);
		exit(1);
	}
	dup2(fd, 1);
}

void	ms_cmd_execute_command_error(t_shell *shell, int tempfd_stdout)
{
	dup2(tempfd_stdout, 1);
	ft_putstr(COLOR_RED);
	printf("Command not found: \'%s\'\n", shell->cmd->argv[0]);
	ft_putstr(COLOR_RESET);
	ms_cmd_argv_free(shell->cmd);
	ms_shell_destroy(shell);
	exit(1);
}
