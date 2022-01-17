#include "minishell.h"

static t_tree	*ms_parse_cmdline_1(t_shell *shell);
static t_tree	*ms_parse_cmdline_2(t_shell *shell);
static t_tree	*ms_parse_cmdline_3(t_shell *shell);
static t_tree	*ms_parse_cmdline_4(t_shell *shell);

t_tree	*ms_parse_cmdline(t_shell *shell)
{
	t_lexer	*save;
	t_tree	*node;

	save = shell->templexer;
	node = ms_parse_cmdline_1(shell);
	if (node != NULL)
		return (node);
	shell->templexer = save;
	node = ms_parse_cmdline_2(shell);
	if (node != NULL)
		return (node);
	shell->templexer = save;
	node = ms_parse_cmdline_3(shell);
	if (node != NULL)
		return (node);
	shell->templexer = save;
	node = ms_parse_cmdline_4(shell);
	if (node != NULL)
		return (node);
	shell->templexer = save;
	node = ms_parse_job(shell);
	if (node != NULL)
		return (node);
	return (NULL);
}

static t_tree	*ms_parse_cmdline_1(t_shell *shell)
{
	t_tree	*job_node;
	t_tree	*cmd_node;
	t_tree	*result;

	job_node = ms_parse_job(shell);
	if (job_node == NULL)
		return (NULL);
	if (!ms_parse_lexertype(shell, ';', NULL))
	{
		ms_parse_node_free(job_node);
		return (NULL);
	}
	cmd_node = ms_parse_cmdline(shell);
	if (cmd_node == NULL)
	{
		ms_parse_node_free(job_node);
		return (NULL);
	}
	result = ms_tree_malloc(shell);
	result->type = TREE_SEM;
	result->value = NULL;
	result->left = job_node;
	result->right = cmd_node;
	return (result);
}

static t_tree	*ms_parse_cmdline_2(t_shell *shell)
{
	t_tree	*job_node;
	t_tree	*result;

	job_node = ms_parse_job(shell);
	if (job_node == NULL)
		return (NULL);
	if (!ms_parse_lexertype(shell, ';', NULL))
	{
		ms_parse_node_free(job_node);
		return (NULL);
	}
	result = ms_tree_malloc(shell);
	result->type = TREE_SEM;
	result->value = NULL;
	result->left = job_node;
	result->right = NULL;
	return (result);
}

static t_tree	*ms_parse_cmdline_3(t_shell *shell)
{
	t_tree	*job_node;
	t_tree	*cmd_node;
	t_tree	*result;

	job_node = ms_parse_job(shell);
	if (job_node == NULL)
		return (NULL);
	if (!ms_parse_lexertype(shell, '&', NULL))
	{
		ms_parse_node_free(job_node);
		return (NULL);
	}
	cmd_node = ms_parse_cmdline(shell);
	if (cmd_node == NULL)
	{
		ms_parse_node_free(job_node);
		return (NULL);
	}
	result = ms_tree_malloc(shell);
	result->type = TREE_AMP;
	result->value = NULL;
	result->left = job_node;
	result->right = cmd_node;
	return (result);
}

static t_tree	*ms_parse_cmdline_4(t_shell *shell)
{
	t_tree	*job_node;
	t_tree	*result;

	job_node = ms_parse_job(shell);
	if (job_node == NULL)
		return (NULL);
	if (!ms_parse_lexertype(shell, '&', NULL))
	{
		ms_parse_node_free(job_node);
		return (NULL);
	}
	result = ms_tree_malloc(shell);
	result->type = TREE_AMP;
	result->value = NULL;
	result->left = job_node;
	result->right = NULL;
	return (result);
}
