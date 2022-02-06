#include "libft.h"

int	ft_is_2_q(int c)
{
	return (c == 34);
}

int	ft_is_1_q(int c)
{
	return (c == 39);
}

int	ft_is_q(int c)
{
	return (ft_is_1_q(c) || ft_is_2_q(c));
}