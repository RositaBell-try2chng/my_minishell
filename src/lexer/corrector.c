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

static char	*change_value(char *src, char *value, int flg)
{
	char	*res;
	size_t	i;

	i = 0;
	while (flg && src[i] && src[i] != '=')
		i++;
	if (flg)
		res = ft_strdup(src + i + 1);
	else
		res = ft_strdup(value + 2);
	if (!res)
	{
		ft_putstr("Error: not enough memory(change value)\n", 2);
		return (value);
	}
	free(value);
	return (res);
}

static void	ms_lexerlist_replace_var(t_shell *shell)
{
	t_lexer	*c;
	int		j;
	int 	flg;

	c = shell->lexerlist;
	while (c)
	{
		if (c->value[0] == '$' && c->value[1])
		{
			flg = !(c->value[1] >= '0' && c->value[1] <= '9');
			j = find_variable(shell->envp, (c->value + 1));
			if (j < 0 && flg)
				c->value[0] = '\0';
			else
				c->value = change_value(shell->envp[j], c->value, flg);
		}
		c = c->next;
	}
}

void	ms_lexerlist_corrector(t_shell *shell)
{
	ms_lexerlist_corrector_arrows(shell);
	ms_lexerlist_corrector_amps_pipes(shell);
	ms_lexerlist_replace_var(shell);
}
