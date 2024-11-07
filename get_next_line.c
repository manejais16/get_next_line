#include "get_next_line.h"

//Free the buffer and set buffer pointer to 0
static char *free_buffer(char **buffer);							//Tested
static char *free_current_read(char **current_read);				//Tested
static char *check_for_newline(char *buffer);						//tested
//Don't call this function if there are not bytes read!!!
//This function truncates the buffer!!!!
static char *get_line(char **buffer, char *new_line_start);			//tested
static int	truncate_buffer(char **buffer, char *new_line_start); 	//Tested
static void	ft_strlcpy(char *result, char *buffer, int len); 		//Tested

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

	current_read = (char *)malloc(BUFFER_SIZE);
	if (!current_read)
		return(free_buffer(&buffer));
	while (1)
	{
		new_line_start = check_for_newline(buffer);
		if (new_line_start)
		{
			free_current_read(&current_read);
			return (get_line(&buffer, new_line_start));
		}
		bytes_read = read(fd, current_read, BUFFER_SIZE);
		if (bytes_read == -1 || (bytes_read == 0 && *buffer == '\0') || \
				!add_to_buffer(&buffer, current_read, bytes_read))
		{
			free_buffer(&buffer);
			free_current_read(&current_read);
			return (0);
		}
		if (!check_for_newline(buffer) && bytes_read < BUFFER_SIZE)
		{
			free_buffer(&current_read);
			current_read = get_line(&buffer, new_line_start);
			free_buffer(&buffer);
			return (current_read);
		}	
	}
}


static char *free_buffer(char **buffer)
{
	if (*buffer)
		free (*buffer);
	*buffer = 0;
	return (0);
}

static char *free_current_read(char **current_read)
{
	if (*current_read)
		free (*current_read);
	*current_read = 0;
	return (0);
}

static char *check_for_newline(char *buffer)
{
	while (*buffer)
	{
		if (*buffer == '\n')
			return (++buffer);
		buffer++;
	}
	return (0);
}

static char *get_line(char **buffer, char *new_line_start)
{
	char	*result;

	//Special case if there is no \n in the buffer
	// The buffer still has to be free!!
	// returns 0 if malloc failes
	if (!new_line_start)
	{
		result = (char *)malloc(str_len(*buffer) + NULL_CHAR_LEN);
		if (!result)
			return (0);
		ft_strlcpy(result, *buffer, str_len(*buffer));
		return (result);
	}
	result = (char *)malloc(new_line_start - *buffer + NULL_CHAR_LEN);
	if (!result)
		return(free_buffer(buffer));
	ft_strlcpy(result, *buffer, \
			new_line_start - *buffer);
	//The buffer has to still be free!!
	if (!truncate_buffer(buffer, new_line_start))
		return (0);
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
	ft_strlcpy(result, new_line_start , len);
	free_buffer(buffer);
	*buffer = result;
	return (1);
}

static void	ft_strlcpy(char *result, char *buffer, int len)
{
	*(result + len) = '\0';
	len--;
	while (len >= 0)
	{
		*(result + len) = *(buffer + len);
		len--;
	}
	return ;
}
