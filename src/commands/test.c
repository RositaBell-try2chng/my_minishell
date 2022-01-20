#include "minishell.h"

void	ms_cmd_execute_test(t_shell *shell)
{
	char	*gnl_line;
	int		gnl_counter;

	if (shell->cmd->argc != 1)
		ft_putstr(COLOR_RED"test: parametri ne nuzhny\n"COLOR_RESET, 2);
	else
	{
		gnl_counter = 0;
		while (ft_gnl(0, &gnl_line) != 0)
		{
			printf("%s\n", gnl_line);
			gnl_counter++;
			free(gnl_line);
		}
		if (ft_strlen(gnl_line) > 0)
			gnl_counter++;
		usleep(1000000);
		if (gnl_counter > 0)
			printf("kolichestvo strok = %d\n", gnl_counter);
		free(gnl_line);
	}
}
