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

// GAME
void	display_board(int *board, int num_heaps);
int		ai_move(int *board, int num_heaps);
int		get_player_move(int *board, int num_heaps);
void	play_game(int *board, int num_heaps);
int		is_game_over(int *board, int num_heaps);
int		find_last_heap(int *board, int num_heaps);
void	print_number(int n);

#endif
