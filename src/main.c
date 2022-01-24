#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	ms_shell_starterror(argc, argv);
	shell = ms_shell_init();
	shell->envp = envp_cpy(envp, shell);
	while (1)
	{
		ms_readline_and_lexerlist(shell);
		if (shell->lexercount > 0 && MS_TEST_REGIME == 1)
			ms_lexerlist_print(shell);
		if (ms_lexerlist_parse(shell) == 0)
		{
			if (MS_TEST_REGIME == 1)
				ms_lexertree_print(shell);
			ms_tree_execute(shell);
		}
		ms_lexerlist_destroy(shell);
		ms_parse_tree_destroy(shell);
		ms_trlist_destroy(shell);
	}
	return (0);
}
