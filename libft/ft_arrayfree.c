#include "libft.h"

void	ft_arrayfree(void ***array, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free((*array)[i]);
		(*array)[i] = NULL;
		i++;
	}
	free(*array);
	*array = NULL;
}
