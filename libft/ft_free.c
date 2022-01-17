#include "libft.h"

void	ft_free(void **pointer)
{
	free(*pointer);
	*pointer = NULL;
}
