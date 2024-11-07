/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 05:24:51 by kzarins           #+#    #+#             */
/*   Updated: 2024/11/07 23:21:04 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
//FOR DEBUGING!!!
# include <stdio.h>
# include <unistd.h>

char	*get_next_line(int fd);
int		add_to_buffer(char **buffer, char *current_read, int bytes_read);
int		str_len(char *str);
void	ft_strlcpy(char *result, char *buffer, int len);
char	*free_buffer(char **buffer, char **buffer2);
char	*check_for_newline(char *buffer);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42 
# endif
# define NULL_CHAR_LEN 1 

#endif
