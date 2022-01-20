#include "minishell.h"

void	ms_cmd_execute_pwd(t_shell *shell)
{
	char	cwd[1000];

	(void)shell;
	if (getcwd(cwd, 999) != NULL)
	{
		printf("%s\n", cwd);
	}
	else
	{
		ft_putstr(COLOR_RED);
		perror("Error with getcwd()");
		ft_putstr(COLOR_RESET);
	}
}
