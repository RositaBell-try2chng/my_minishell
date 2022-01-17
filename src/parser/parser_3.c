#include "minishell.h"

static t_tree	*ms_parse_lexerlist(t_shell *shell);
static t_tree	*ms_parse_lexerlist_1(t_shell *shell);

t_tree	*ms_parse_simplecmd(t_shell *shell)
{
	t_tree	*lexerlist_node;
	t_tree	*result;
	char	*lexer_value;

	if (!ms_parse_lexertype(shell, -1, &lexer_value))
		return (NULL);
	lexerlist_node = ms_parse_lexerlist(shell);
	result = ms_tree_malloc(shell);
	result->type = TREE_FILE;
	if (lexer_value != NULL)
		result->value = lexer_value;
	result->left = NULL;
	result->right = lexerlist_node;
	return (result);
}

static t_tree	*ms_parse_lexerlist(t_shell *shell)
{
	t_lexer	*save;
	t_tree	*node;

	save = shell->templexer;
	node = ms_parse_lexerlist_1(shell);
	if (node != NULL)
		return (node);
	shell->templexer = save;
	return (NULL);
}

static t_tree	*ms_parse_lexerlist_1(t_shell *shell)
{
	t_tree	*lexerlist_node;
	t_tree	*result;
	char	*lexer_value;

	if (!ms_parse_lexertype(shell, -1, &lexer_value))
		return (NULL);
	lexerlist_node = ms_parse_lexerlist(shell);
	result = ms_tree_malloc(shell);
	result->type = TREE_ARG;
	if (lexer_value != NULL)
		result->value = lexer_value;
	result->left = NULL;
	result->right = lexerlist_node;
	return (result);
}
