#include "aicu.h"

int	is_valid(const char *line, int *size)
{
	long	num;
	int	i;

	num = 0;
	i = 0;
	if (!line || *line == '\0')
		return (0);
	while (line[i])
	{
		if (line[i] < '0' || line[i] > '9')
			return (0);
		if (num > MAX_ITEMS || (num == MAX_ITEMS && (line[i] - '0') > 0))
			return (0);
		num = num * 10 + (line[i] - '0');
		i++;
	}
	if (num > MIN_ITEMS || num > MAX_ITEMS)
		return (0);
	*size = (int)num;
	return (1);
}

void	free_board(int *board)
{
	if (board)
		free(board);
}

int	*read_board(int fd, int *num_heaps)
{
	int		*heaps = NULL;
	char	*line;
	int		count = 0;
	int		size = 0;
	int		*old_heaps;
	int		i;

	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL) 
			break;
		if (fd == STDIN_FILENO && *line == '\0')
		{
			free(line);
			break;
		}
		if (!is_valid(line, &size))
		{
			write(STDERR_FILENO, ERROR_MESSAGE, 6);
			free(line);
			free_board(heaps);
			return (NULL);
		}
		old_heaps = heaps; 
		heaps = (int *)malloc((count + 1) * sizeof(int));
		if (!heaps)
		{
			free(line);
			free_board(old_heaps); 
			return (NULL); 
		}
		i = 0;
		while (i < count)
		{
			heaps[i] = old_heaps[i];
			i++;
		}
		if (old_heaps)
			free(old_heaps);

		heaps[count++] = size;
		free(line);
	}
	*num_heaps = count;
	return (heaps);
}
