#include "libft.h"

static void	*ft_mg_pathjoin(void *dst, const void *src, int if_slash)
{
	if (src != NULL)
		dst = ft_memjoin(dst, src);
	if (if_slash == 1)
		dst = ft_memjoin(dst, "/");
	return (dst);
}

static int	ft_mg_compare(char *s1, char *s2)
{
	if (ft_strcmp(s2, ".") == 0 || ft_strcmp(s2, "..") == 0)
		return (0);
	if ((!*s1 && !*s2))
		return (1);
	else if (*s1 == '?' && *s2)
		return (ft_mg_compare(s1 + 1, s2 + 1));
	else if (*s1 == '*' && s1[1] == '*')
		return (ft_mg_compare(s1 + 1, s2));
	else if (*s1 == '*' && *s2 == s1[1])
		return (ft_mg_compare(s1 + 1, s2) || ft_mg_compare(s1, s2 + 1));
	else if (*s1 == '*' && *s2 != s1[1] && *s2)
		return (ft_mg_compare(s1, s2 + 1));
	else if (*s1 == '\\' && *s2 == s1[1]
		&& (s1[1] == '*' || s1[1] == '?' || s1[1] == '{' || s1[1] == '['))
		return (ft_mg_compare(s1 + 2, s2 + 1));
	else if (*s1 == *s2)
		return (ft_mg_compare(s1 + 1, s2 + 1));
	return (0);
}

static char	**ft_mg_filesarray(char files_names[1000][250], int files_count)
{
	char	**files_tmp;
	int		i;

	files_tmp = malloc(sizeof(char *) * (files_count + 1));
	if (files_tmp == NULL)
		return (NULL);
	i = 0;
	while (i < files_count)
	{
		files_tmp[i] = malloc(sizeof(char) * ft_strlen(files_names[i]) + 1);
		if (files_tmp[i] == NULL)
		{
			ft_arrayfree((void ***)&files_tmp, i);
			return (NULL);
		}
		ft_strcpy(files_tmp[i], files_names[i]);
		i++;
	}
	files_tmp[i] = NULL;
	return (files_tmp);
}

static int	ft_mg_scandir(char *scandir, char *filepattern,
	char ***files, int files_count)
{
	DIR				*dir;
	struct dirent	*file;
	char			files_names[1000][250];

	dir = opendir(scandir);
	if (dir == NULL && (errno == ENOENT || errno == ENOTDIR))
		return (0);
	if (dir == NULL && errno != ENOENT && errno != ENOTDIR)
		return (-2);
	while (1)
	{
		file = readdir(dir);
		if (file == NULL)
			break ;
		if (ft_mg_compare(filepattern, file->d_name) == 1)
		{
			ft_strcpy((char *)files_names[files_count], scandir);
			ft_mg_pathjoin((char *)files_names[files_count++], file->d_name, 0);
		}
	}
	closedir(dir);
	*files = ft_mg_filesarray(files_names, files_count);
	if (*files == NULL)
		return (-1);
	return (files_count);
}

int	ft_miniglob(char *pattern, char ***files)
{
	char	scandir[1000];
	char	filepattern[250];
	char	**filepattern_array;
	int		filepattern_count;
	int		i;

	*files = NULL;
	if (ft_strlen(pattern) == 0 || pattern[ft_strlen(pattern) - 1] == '/')
		return (0);
	filepattern_count = ft_split_count(pattern, '/');
	filepattern_array = ft_split(pattern, '/');
	if (filepattern_array == NULL)
		return (-1);
	scandir[0] = '\0';
	if (pattern[0] == '/')
		ft_mg_pathjoin(scandir, NULL, 1);
	i = 0;
	while (i < filepattern_count - 1)
		ft_mg_pathjoin(scandir, filepattern_array[i++], 1);
	ft_strcpy(filepattern, filepattern_array[filepattern_count - 1]);
	ft_arrayfree((void ***)&filepattern_array, filepattern_count);
	return (ft_mg_scandir(scandir, filepattern, files, 0));
}
