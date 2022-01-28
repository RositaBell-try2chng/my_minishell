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

static void	ms_replace_variable(char *dst, char *src, t_shell *shell)
{
	size_t	i_ds;
	size_t	i_sr;

	i_sr = 0;
	i_ds = 0;
	while (src[i_sr])
	{
		if (src[i_sr] == '$' && ft_isalpha(src[i_sr + 1]))
			i_sr += copy_var(dst + i_ds, src + i_sr + 1, shell, &i_ds) + 1;
		else if (src[i_sr] == '$' && src[i_sr + 1] == '?')
			i_sr += copy_var(dst + i_ds, (char *)shell, shell, &i_ds);
		else if (src[i_sr] == '$' && src[i_sr + 1] > 47 && src[i_sr + 1] < 58)
			i_sr += 2;
		else
			dst[i_ds++] = src[i_sr++];
	}
	dst[i_ds] = 0;
}

static void	ms_lexerlist_replace_var(t_shell *shell)
{
	t_lexer	*c;
	char	*tmp;
	int 	flg_dollar;

	c = shell->lexerlist;
	while (c)
	{
		flg_dollar = ft_str_real_len(c->value, shell);
		if (flg_dollar > 0)
		{
			tmp = c->value;
			c->value = malloc(sizeof(char) * (flg_dollar + 1));
			if (!c->value)
			{
				c->value = tmp;
				ft_putstr("Not enough memory\n", 2);
			}
			else
			{
				ms_replace_variable(c->value, tmp, shell);
				free(tmp);
			}
		}
		c = c->next;
	}
}

void	ms_lexerlist_corrector(t_shell *shell)
{
	char *tmp;

	ms_lexerlist_corrector_arrows(shell);
	ms_lexerlist_corrector_amps_pipes(shell);
	tmp = shell->st;
	shell->st = ft_itoa(shell->status);
	if (!shell->st)
		shell->st = tmp;
	else
		free(tmp);
	ms_lexerlist_replace_var(shell);
}
