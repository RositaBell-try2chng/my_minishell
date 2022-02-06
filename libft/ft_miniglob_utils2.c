#include "libft.h"

//Подготовительные действия перед сканированием папки
void	mg_before_scandirs(t_glob *glob)
{
	mg_glob_scandirs_destroy(glob);
	glob->scandirs = glob->folders;
	glob->folders = NULL;
	glob->t_scandirs = glob->scandirs;
	glob->folders_count = 0;
}

//Запускается, если произошла ошибка
int	mg_destroy_if_malloc_error(t_glob *glob, int ret)
{
	if (glob->malloc_error == 1)
		mg_miniglob_destroy(glob);
	return (ret);
}
