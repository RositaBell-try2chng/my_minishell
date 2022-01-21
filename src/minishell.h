#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
//# include <assert.h>
//# include <stdlib.h>
//# include <unistd.h>
//# include <string.h>
//# include <pwd.h>
//# include <sys/types.h>
//# include <dirent.h>
//# include <errno.h>

# define OS_VERSION				2 // 1 - MAC, 2 - LINUX
# define MSH_DEFNAME			"MiniShell"
# define MS_TEST_REGIME			0 // 1 - Test info, 0 - No test info
# define MS_READLINE_REGIME		1 // 1 - ReadLine (history), 2 - GNL (no leaks)
# define COLOR_GREEN			"\x1b[38;5;118m"
# define COLOR_RED				"\x1b[38;5;196m"
# define COLOR_ORANGE			"\x1b[38;5;208m"
# define COLOR_BLUE				"\x1b[1;40;36m"
# define COLOR_RESET			"\x1b[0m"
# define LEXER_STATE_DEFAULT	0
# define LEXER_STATE_DQUOTES	1
# define LEXER_STATE_QUOTES		2
# define TREE_PIPE				1
# define TREE_AMP				2
# define TREE_SEM				3
# define TREE_REDIN				4
# define TREE_REDOUT			5
# define TREE_FILE				6
# define TREE_ARG				7

typedef struct s_lexer	t_lexer;
typedef struct s_tree	t_tree;
typedef struct s_trlist	t_trlist;
typedef struct s_cmd	t_cmd;
typedef struct s_shell	t_shell;

typedef struct s_lexer
{
	int			type;
	char		*value;
	t_lexer		*next;
}	t_lexer;

typedef struct s_tree
{
	int			type;
	char		*value;
	t_trlist	*list;
	t_tree		*left;
	t_tree		*right;
}	t_tree;

typedef struct s_trlist
{
	t_tree		*node;
	bool		clear;
	t_trlist	*next;
}	t_trlist;

typedef struct s_cmd
{
	int			argc;
	char		**argv;
	bool		async;
	bool		stdin_pipe;
	bool		stdout_pipe;
	int			pipe_read;
	int			pipe_write;
	char		*redirect_in;
	char		*redirect_out;
}	t_cmd;

typedef struct s_shell
{
	int			output_error;
	char		*prompt_name;
	char		*prompt_line;
	char		*input;
	int			inputlen;
	int			input_i;
	int			input_c;
	bool		sigset;
	void		(*sigint_fun)(int);
	int			lexerstate;
	int			lexercount;
	t_lexer		*lexerlist;
	t_lexer		*templexer;
	int			lexval_i;
	t_tree		*lexertree;
	t_trlist	*trlist;
	t_trlist	*temptrlist;
	t_cmd		*cmd;
	char		**envp;
}	t_shell;

//Ruslan :)
char	**envp_cpy(char **env);

//puts.c
void	ft_putstr(char *str, int std_var);
void	ft_puterror(t_shell *shell, int code, char *name);
void	ft_puterror_noexit(t_shell *shell, int code);
void	ft_putexit(t_shell *shell);

// main_utils.c
void	ms_shell_starterror(int argc, char **argv);
t_shell	*ms_shell_init(void);
void	ms_readline_and_lexerlist(t_shell *shell);
void	ms_shell_destroy(t_shell *shell);

//signals.c
void	ms_ignore_signals(t_shell *shell);
void	ms_sigint_in_child(t_shell *shell);

//lexer
int		ms_lexer_chartype(char c);
t_lexer	*ms_lexerlist_add(t_shell *shell, int value_length);
void	ms_lexerlist_build(t_shell *shell);
void	ms_lexer_parser(t_shell *shell);
void	ms_lexerlist_destroy(t_shell *shell);

//parser
t_tree	*ms_tree_malloc(t_shell *shell);
bool	ms_parse_lexertype(t_shell *shell, int lexertype, char **bufptr);
int		ms_lexerlist_parse(t_shell *shell);
t_tree	*ms_parse_cmdline(t_shell *shell);
t_tree	*ms_parse_job(t_shell *shell);
t_tree	*ms_parse_simplecmd(t_shell *shell);
void	ms_parse_node_free(t_tree *node);
void	ms_parse_tree_destroy(t_shell *shell);
void	ms_trlist_destroy(t_shell *shell);

//executor
void	ms_tree_execute_cmd_hlp(t_shell *shell, bool async, bool p_i, bool p_o);
void	ms_tree_execute_cmd(t_shell *shell, t_tree *node, int p_r, int p_w);
void	ms_tree_execute(t_shell *shell);
void	ms_cmd_argv_free(t_cmd *cmd);
void	ms_cmd_execute_fork(t_shell *shell);
void	ms_cmd_execute_fork_error(void);
void	ms_cmd_execute_fd_null(t_shell *shell);
void	ms_cmd_execute_fd_redirect_in(t_shell *shell);
void	ms_cmd_execute_fd_redirect_out(t_shell *shell);
void	ms_cmd_execute_command_error(t_shell *shell, int tempfd_stdout);
void	do_shell_command(t_shell *shell);

//commands
void	ms_cmd_execute_cd(t_shell *shell);
void	ms_cmd_execute_prompt(t_shell *shell);
void	ms_prompt_name(t_shell *shell, char *name);
void	ms_prompt_cwd(t_shell *shell);
void	ms_cmd_execute_pwd(t_shell *shell);
void	ms_cmd_execute_exit(t_shell *shell);
void	ms_cmd_execute_test(t_shell *shell);
void	ms_cmd_execute_export(t_shell *shell);
void	ms_cmd_execute_env(t_shell *shell);
void	ms_cmd_execute_unset(t_shell *shell);
void	ms_cmd_execute_echo(t_shell *shell);
int		count_correct_var(t_shell *shell, char **argv, int argc);

//test-info
void	ms_lexerlist_print(t_shell *shell);
void	ms_lexertree_print(t_shell *shell);
void	ms_cmd_print(t_cmd *cmd);

#endif
