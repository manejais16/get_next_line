static int	str_len(char *str);
static int	free_memory(char *buffer, char *current_read);

int	add_to_buffer(char *buffer, char *current_read, int bytes_read)
{
	char	*result;
	int		len_counter;
	int		iter;

	len_counter = 0;
	*result = (char *) malloc(str_len(buffer) + bytes_read + NULL_CHAR_LEN);
	if (!result)
		return (free_memory(buffer, current_read));
	while (*buffer)
	{
		*(result + len_counter) = *(buffer + len_counter);
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
	buffer = result;
	free_memory(result, current_read);
	return (iter);
}

static int	str_len(char *str)
{
	int	len;

	while (*str)
		len++;
	return (len);
}

static int	free_memory(char *buffer, char *current_read)
{
	free(buffer);
	free(current_read);
	return (-1);
}
