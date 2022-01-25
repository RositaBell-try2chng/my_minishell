#include "minishell.h"

t_tree	*ms_parse_cmd_1_dbl(t_shell *shell)
{
	t_tree	*simplecmd_node;
	t_tree	*result;
	char	*lexer_value;

	simplecmd_node = ms_parse_simplecmd(shell);
	if (simplecmd_node == NULL)
		return (NULL);
	if (!ms_parse_lexertype(shell, LEXER_TYPE_DLBIN, NULL))
	{
		ms_parse_node_free(simplecmd_node);
		return (NULL);
	}
	if (!ms_parse_lexertype(shell, -1, &lexer_value))
	{
		ms_parse_node_free(simplecmd_node);
		return (NULL);
	}
	result = ms_tree_malloc(shell);
	result->type = TREE_DBLIN;
	if (lexer_value != NULL)
		result->value = lexer_value;
	result->left = NULL;
	result->right = simplecmd_node;
	return (result);
}

t_tree	*ms_parse_cmd_2_dbl(t_shell *shell)
{
	t_tree	*simplecmd_node;
	t_tree	*result;
	char	*lexer_value;

	simplecmd_node = ms_parse_simplecmd(shell);
	if (simplecmd_node == NULL)
		return (NULL);
	if (!ms_parse_lexertype(shell, LEXER_TYPE_DLBOUT, NULL))
	{
		ms_parse_node_free(simplecmd_node);
		return (NULL);
	}
	if (!ms_parse_lexertype(shell, -1, &lexer_value))
	{
		ms_parse_node_free(simplecmd_node);
		return (NULL);
	}
	result = ms_tree_malloc(shell);
	result->type = TREE_DBLOUT;
	if (lexer_value != NULL)
		result->value = lexer_value;
	result->left = NULL;
	result->right = simplecmd_node;
	return (result);
}
