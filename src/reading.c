#include "aicu.h"


static char	stash[BUFFER_SIZE + 1];
static int	i = 0;
static int	bytes_read = 0;

int	read_next_char(char *buf, int fd)
{
	if (i == bytes_read)
	{
		bytes_read = read(fd, stash, BUFFER_SIZE);
		
		if (bytes_read < 0)
			return (-1); // Read error
		if (bytes_read == 0)
			return (0); // EOF
			
		stash[bytes_read] = '\0';
		i = 0;
	}
	*buf = stash[i++];
	return (1);
}

char	*get_next_line(int fd)
{
	char	buf;
	int		status;
	size_t	len = 0;
	char	*line = NULL;
	char	*tmp;

	while (1)
	{
		status = read_next_char(&buf, fd);

		if (status == -1)
		{
			free(line);
			return (NULL);
		}
		if (status == 0)
			break ;
		if (fd == STDIN_FILENO && len == 0 && buf == '\n')
		{
			line = (char *)malloc(1); 
			if (!line) return (NULL);
			line[0] = '\0';
			return (line);
		}
		if (buf == '\n')
			break ;
		tmp = (char *)malloc(len + 2); 
		if (!tmp)
		{
			free(line);
			return (NULL);
		}
		if (line)
		{
			size_t i = 0;
			while (i < len)
			{
				tmp[i] = line[i];
				i++;
			}
			free(line);
		}
		
		line = tmp;
		line[len] = buf;
		len++;
	}
	if (len == 0)
		return (NULL);
	line[len] = '\0';
	return (line);
}
