#include "minishell.h"

static int	ms_cmd_execute_command(t_shell *shell)
{
	if (ft_strcmp(shell->cmd->argv[0], "pwd") == 0)
		ms_cmd_execute_pwd(shell);
	return (0);
}

static void	ms_execute_zombie_handler(int signum)
{
	int		stop;
	pid_t	pid;

	(void)signum;
	stop = 0;
	while (stop == 0)
	{
		pid = waitpid(-1, NULL, WNOHANG); // Вместо NULL был status
		if (pid > 0)
			printf("Process %d terminated\n", pid);
		if (pid <= 0)
			stop = 1;
	}
}

static void	ms_cmd_execute_after_fork(t_shell *shell, pid_t pid)
{
	struct sigaction	act;

	if (shell->cmd->async == 0)
		waitpid(pid, NULL, 0);
	if (shell->cmd->async == 1)
	{
		printf("Process %d started\n", pid);
		act.sa_flags = 0;
		act.sa_handler = ms_execute_zombie_handler;
		//sigfillset(&(act.sa_mask)); // to block all
		if (sigaction(SIGCHLD, &act, NULL) != 0)
		{
			ft_putstr(COLOR_RED);
			perror("Error with sigaction()");
			ft_putstr(COLOR_RESET);
		}
	}
}

void	ms_cmd_execute_fork(t_shell *shell)
{
	pid_t	pid;
	int		tempfd_stdout;

	pid = fork();
	if (pid < 0)
		return (ms_cmd_execute_fork_error());
	if (pid == 0)
	{
		ms_sigint_in_child(shell);
		tempfd_stdout = dup(1);
		if (shell->cmd->async == 1)
			ms_cmd_execute_fd_null(shell);
		if (shell->cmd->redirect_in)
			ms_cmd_execute_fd_redirect_in(shell);
		else if (shell->cmd->redirect_out)
			ms_cmd_execute_fd_redirect_out(shell);
		if (shell->cmd->stdin_pipe)
			dup2(shell->cmd->pipe_read, 0);
		if (shell->cmd->stdout_pipe)
			dup2(shell->cmd->pipe_write, 1);
		if (ms_cmd_execute_command(shell) == 0)
			ms_cmd_execute_command_error(shell, tempfd_stdout);
	}
	ms_cmd_execute_after_fork(shell, pid);
}
