#include "minishell.h"

static t_tree	*ms_parse_job_1(t_shell *shell);
static t_tree	*ms_parse_cmd(t_shell *shell);
static t_tree	*ms_parse_cmd_1(t_shell *shell);
static t_tree	*ms_parse_cmd_2(t_shell *shell);

t_tree	*ms_parse_job(t_shell *shell)
{
	t_lexer	*save;
	t_tree	*node;

	save = shell->templexer;
	node = ms_parse_job_1(shell);
	if (node != NULL)
		return (node);
	shell->templexer = save;
	node = ms_parse_cmd(shell);
	if (node != NULL)
		return (node);
	return (NULL);
}

static t_tree	*ms_parse_job_1(t_shell *shell)
{
	t_tree	*cmd_node;
	t_tree	*job_node;
	t_tree	*result;

	cmd_node = ms_parse_cmd(shell);
	if (cmd_node == NULL)
		return (NULL);
	if (!ms_parse_lexertype(shell, '|', NULL))
	{
		ms_parse_node_free(cmd_node);
		return (NULL);
	}
	job_node = ms_parse_job(shell);
	if (job_node == NULL)
	{
		ms_parse_node_free(cmd_node);
		return (NULL);
	}
	result = ms_tree_malloc(shell);
	result->type = TREE_PIPE;
	result->value = NULL;
	result->left = cmd_node;
	result->right = job_node;
	return (result);
}

static t_tree	*ms_parse_cmd(t_shell *shell)
{
	t_lexer	*save;
	t_tree	*node;

	save = shell->templexer;
	node = ms_parse_cmd_1(shell);
	if (node != NULL)
		return (node);
	shell->templexer = save;
	node = ms_parse_cmd_1_dbl(shell);
	if (node != NULL)
		return (node);
	shell->templexer = save;
	node = ms_parse_cmd_2(shell);
	if (node != NULL)
		return (node);
	shell->templexer = save;
	node = ms_parse_cmd_2_dbl(shell);
	if (node != NULL)
		return (node);
	shell->templexer = save;
	node = ms_parse_simplecmd(shell);
	if (node != NULL)
		return (node);
	return (NULL);
}

static t_tree	*ms_parse_cmd_1(t_shell *shell)
{
	t_tree	*simplecmd_node;
	t_tree	*result;
	char	*lexer_value;

	simplecmd_node = ms_parse_simplecmd(shell);
	if (simplecmd_node == NULL)
		return (NULL);
	if (!ms_parse_lexertype(shell, '<', NULL))
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
	result->type = TREE_REDIN;
	if (lexer_value != NULL)
		result->value = lexer_value;
	result->left = NULL;
	result->right = simplecmd_node;
	return (result);
}

static t_tree	*ms_parse_cmd_2(t_shell *shell)
{
	t_tree	*simplecmd_node;
	t_tree	*result;
	char	*lexer_value;

	simplecmd_node = ms_parse_simplecmd(shell);
	if (simplecmd_node == NULL)
		return (NULL);
	if (!ms_parse_lexertype(shell, '>', NULL))
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
	result->type = TREE_REDOUT;
	if (lexer_value != NULL)
		result->value = lexer_value;
	result->left = NULL;
	result->right = simplecmd_node;
	return (result);
}
