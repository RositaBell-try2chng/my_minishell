#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
//# include <stdio.h>
# include <stdlib.h>
//# include <fcntl.h>
# include <dirent.h>
# include <errno.h>

# define GNL_BUFF_SIZE	32

int		ft_strlen(const char *str);
char	*ft_strcpy(char *dst, const char *src);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s);
int		ft_split_count(char const *str, char c);
void	*ft_memset(void *str, int c, size_t len);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memjoin(void *dst, const void *src);
char	**ft_split(char const *s, char c);
int		ft_gnl(int fd, char **line);
int		ft_miniglob(char *pathpattern, char ***files);
void	ft_arrayfree(void ***array, size_t count);
void	ft_free(void **pointer);

#endif
