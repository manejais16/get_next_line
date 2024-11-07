#include "get_next_line.h"
int	str_len(char *str); //Tested

//If theres are no read bytes the buffer does not get changed
//In that case the function returns -1
int	add_to_buffer(char **buffer, char *current_read, int bytes_read)
{
	char	*result;
	int		len_counter;
	int		iter;

	if (!bytes_read)
		return (-1);
	result = (char *) malloc(str_len(*buffer) + bytes_read + NULL_CHAR_LEN);
	if (!result)
		return (0);
	len_counter = 0;
	while (*(*buffer + len_counter))
	{
		*(result + len_counter) = *(*buffer + len_counter);
		len_counter++;
	}
	iter = 0;
	while (iter < bytes_read)
	{
		*(result + len_counter) = *(current_read + iter);
		len_counter++;
		iter++;
	}
	*(result + len_counter) = '\0';
	free(*buffer);
	*buffer = result;
	return (iter);
}

int	str_len(char *str)
{
	int	len;

	len = 0;
	while (*str)
	{
		len++;
		str++;
	}
	return (len);
}
