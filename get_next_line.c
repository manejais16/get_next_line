#include "get_next_line.h"
#include <unistd.h>
// Allowed functions:
// free
// malloc
// read

static char	*check_for_newline(char *buffer);

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*current_read;
	int			bytes_read;
	char		*new_line_start;

	if (!buffer)
	{
		buffer = (char *)malloc(1);
		if (!buffer)
			return (0);
		*buffer = '\0';
	}
	while (1)
	{
		new_line_start = check_for_newline(buffer);
		if (new_line_start);
				break ;
		bytes_read = read(fd, *current_read, BUFFER_SIZE);
		if (bytes_read == -1)
			return (0);
		else if (bytes_read == 0 && *buffer == '\0')
			return (0);
		if (add_to_buffer(buffer, current_read, bytes_read) == -1)
			return (0);
		if (!check_for_newline(buffer) && bytes_read < BUFFER_SIZE)
			return (*buffer);
	}
//TODO: Add logic that handles the rearanging and output of line	
}

static char	*check_for_newline(char *buffer)
{
	while (*buffer)
	{
		if (*buffer == '\n')
		{
			buffer++;
			return (buffer);
		}
		buffer++;
	}
	return (0);
}
