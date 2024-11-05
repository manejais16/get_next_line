#include "get_next_line.h"
#include <unistd.h>
// Allowed functions:
// free
// malloc
// read

static char	*check_for_newline(char *buffer);
static char	*get_line(char **buffer,char *new_line_start);
static int	truncate_buffer(char **buffer, char *new_line_start);
static void	ft_strlcpy(char *result, char *buffer, int len);

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*current_read;
	int			bytes_read;
	char		*new_line_start;

	current_read = (char *)malloc(BUFFER_SIZE);
	if (!current_read)
		return (0);
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
		if (new_line_start)
			return (get_line(&buffer, new_line_start));
		bytes_read = read(fd, current_read, BUFFER_SIZE);
		if (bytes_read == -1)
			return (0);
		else if (bytes_read == 0 && *buffer == '\0')
			return (0);
		if (add_to_buffer(&buffer, current_read, bytes_read) == -1)
			return (0);
		if (!check_for_newline(buffer) && bytes_read < BUFFER_SIZE)
			return (get_line(&buffer, new_line_start));
	}
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

static char	*get_line(char **buffer,char *new_line_start)
{
	char	*result;
	
	if (!new_line_start)
		return(*buffer);
	result = (char *)malloc(new_line_start - *buffer + NULL_CHAR_LEN);
	if (!result)
	{
		free (*buffer);
		return (0);
	}
	ft_strlcpy(result, *buffer, \
			new_line_start - *buffer + NULL_CHAR_LEN);
	if (!truncate_buffer(buffer, new_line_start))
	{
		free (*buffer);
		return (0);
	}
	return (result);
}

static int	truncate_buffer(char **buffer, char *new_line_start)
{
	char	*result;
	int		len;

	len = str_len(*buffer) - (new_line_start - *buffer);
	result = (char *)malloc(len + NULL_CHAR_LEN);
	if (!result)
		return (0);
	ft_strlcpy(result, new_line_start, len + NULL_CHAR_LEN);
	free(*buffer);
	*buffer = result;
	return (1);
}

static void	ft_strlcpy(char *result, char *buffer, int len)
{
	len--;	
	*(result + len) = '\0';
	len--;
	while (len >= 0)
	{
		*(result + len) = *(buffer + len);
		len--;
	}
	return ;
}
