#include "minishell.h"

static void	ms_lexerlist_free(t_lexer *lexerlist)
{
	if (lexerlist->value != NULL)
		ft_free((void **)&lexerlist->value);
	if (lexerlist->next != NULL)
		ms_lexerlist_free(lexerlist->next);
	ft_free((void **)&lexerlist);
}

void	ms_lexerlist_destroy(t_shell *shell)
{
	if (shell->lexerlist != NULL)
	{
		ms_lexerlist_free(shell->lexerlist);
		shell->lexerlist = NULL;
	}
}