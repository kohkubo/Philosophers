#ifndef LIBEX_H
# define LIBEX_H
# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>

bool	is_available_pid(int pid);
bool	is_num_string(char *s);
bool	is_space_string(char *s);
char	**free_string_array(char **buf);
char	**str_arraydup(char **array);
char	*ft_strndup(const char *s1, size_t n);
char	*ft_xstrdup(const char *s1);
char	*random_string(size_t size);
int		arraylen(char **array);
int		contain(char **array, char *word);
int		debug_arraycmp(char **aa, char **bb);
int		ft_isspace(int c);
int		ft_strcmp(const char *s1, const char *s2);
int		get_next_line(int fd, char **line);
long	ft_atol(const char *s);
size_t	ft_min_size_t(size_t a, size_t b);
size_t	spacelen(char *s);
void	*ft_xcalloc(size_t count, size_t size);
void	*ft_xmalloc(size_t size);
void	free_set(void **dst, void *src);
void	ft_error_exit(const char *emsg);
void	ft_fatal(const char *emsg);
void	ft_quick_sort(int array[], int left, int right);
void	print_array(char **array);
void	strsort(char *str[], int n);
#endif
