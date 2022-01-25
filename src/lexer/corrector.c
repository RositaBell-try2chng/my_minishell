#include "minishell.h"

static void	ms_lexerlist_corrector_arrows(t_shell *shell)
{
	t_lexer	*templexer;
	char	*value;

	templexer = shell->lexerlist;
	while (templexer->next)
	{
		value = templexer->value;
		if (ft_strlen(value) == 2 && value[0] == '>' && value[1] == '>')
		{
			templexer->type = LEXER_TYPE_DLBOUT;
			shell->lexercount--;
		}
		if (ft_strlen(value) == 2 && value[0] == '<' && value[1] == '<')
		{
			templexer->type = LEXER_TYPE_DLBIN;
			shell->lexercount--;
		}
		if ((ft_strlen(value) > 2 && value[0] == '>' && value[1] == '>')
			|| (ft_strlen(value) > 2 && value[0] == '<' && value[1] == '<'))
		{
			templexer->type = LEXER_TYPE_ERROR;
			shell->lexercount--;
		}
		templexer = templexer->next;
	}
}

static void	ms_lexerlist_corrector_amps_pipes(t_shell *shell)
{
	t_lexer	*templexer;
	char	*value;

	templexer = shell->lexerlist;
	while (templexer->next)
	{
		value = templexer->value;
		if (ft_strlen(value) == 2 && value[0] == '&' && value[1] == '&')
		{
			templexer->type = LEXER_TYPE_DLBAMP;
			shell->lexercount--;
		}
		if (ft_strlen(value) == 2 && value[0] == '|' && value[1] == '|')
		{
			templexer->type = LEXER_TYPE_DLBPIPE;
			shell->lexercount--;
		}
		if ((ft_strlen(value) > 2 && value[0] == '&' && value[1] == '&')
			|| (ft_strlen(value) > 2 && value[0] == '|' && value[1] == '|'))
		{
			templexer->type = LEXER_TYPE_ERROR;
			shell->lexercount--;
		}
		templexer = templexer->next;
	}
}

void	ms_lexerlist_corrector(t_shell *shell)
{
	ms_lexerlist_corrector_arrows(shell);
	ms_lexerlist_corrector_amps_pipes(shell);
}
