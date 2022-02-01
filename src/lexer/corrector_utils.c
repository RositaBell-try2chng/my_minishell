#include "minishell.h"

static int	count_var_len(char *s, int *i, t_shell *shell)
{
	int		k;
	int		j;

	k = 0;
	while (s[k] && s[k] != '$')
		k++;
	j = -1;
	while (++j < shell->env_size - 1)
	{
		if (!ft_strncmp(shell->envp[j], s, k) && shell->envp[j][k] == '=')
			break ;
	}
	*i = *i + k;
	if (j < shell->env_size - 1)
		return (ft_strlen(shell->envp[j] + k + 1));
	return (0);
}

static void	counts(int *res, int *i, char *s, int *flg)
{
	*flg = 1;
	(*i) += 1;
	(*res) += ft_strlen(s);
}

int	ft_str_real_len(char *s, t_shell *shell)
{
	int res;
	int i;
	int flg;

	res = 0;
	i = 0;
	flg = -1;
	while (s[i])
	{
		if (s[i] == '$' && ft_isalpha(s[i + 1]))
		{
			flg = 1;
			res += count_var_len(s + i + 1, &i, shell);
		}
		else if (s[i] == '$' && s[i + 1] == '?')
			counts(&res, &i, shell->st, &flg);
		else if (s[i] == '$' && s[i + 1] > 47 && s[i + 1] < 58)
			counts(&res, &i, "", &flg);
		else
		{
			res++;
			i++;
		}
	}
	return (res * flg);
}

static int count_offset_dst(char *dst, int j, t_shell *shell, char *s)
{
	int res;

	res = 0;
	if (j == shell->env_size - 1)
		return (res);
	res = ft_strlen(s);
	ft_memcpy((void *)dst, (void *)s, res);
	return (res);
}

size_t	copy_var(char *dst, char *src, t_shell *shell, size_t *i_dst)
{
	size_t	i;
	int		j;
	int		k;

	i = -1;
	j = -1;
	k = 0;
	if ((t_shell *)src == shell)
	{
		while (shell->st[++i])
			dst[i] = shell->st[i];
		*i_dst = *i_dst + i;
		return (2);
	}
	while (src[k] && src[k] != '$')
		k++;
	while (++j < shell->env_size - 1)
	{
		if (!ft_strncmp(shell->envp[j], src, k) && shell->envp[j][k] == '=')
			break ;
	}
	*i_dst += count_offset_dst(dst, j, shell, shell->envp[j] + k + 1);
	return (k);
}