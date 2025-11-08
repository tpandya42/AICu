#ifndef AICU_H
#define AICU_H

#ifndef	BUFFER_SIZE
# define BUFFER_SIZE 4096
#endif

# define MIN_ITEMS 1 
# define MAX_ITEMS 10000
# define ERROR_MESSAGE "ERROR\n"

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

// UTILS
size_t				ft_strlen(const char *str);
int					ft_strcmp(char *s1, char *s2);
void				ft_strcpy(char *dest, const char *src);
char				*ft_strdup(const char *src);

void	free_board(int *board);

// READING
int					read_next_char(char *buf, int fd);
char					*get_next_line(int fd);
int	*read_board(int fd, int *num_heaps);
#endif
