/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andqueir <andqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 16:35:38 by andqueir          #+#    #+#             */
/*   Updated: 2025/11/20 18:20:05 by andqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*help_free(char *buffer, char *temp)
{
	char	*tmp;

	tmp = ft_strjoin(buffer, temp);
	if (!tmp)
	{
		free(buffer);
		return (NULL);
	}
	free(buffer);
	return (tmp);
}

char	*shift_buffer(char *buffer)
{
	int		i;
	int		j;
	char	*next;

	i = 0;
	j = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	next = ft_calloc(ft_strlen(buffer), sizeof(char));
	if (!next)
		return (NULL);
	i++;
	while (buffer[i])
		next[j++] = buffer[i++];
	return (next);
}

char	*get_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc((i + (buffer[i] == '\n') + 1), sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*read_file(int fd, char *stash, char buffer[BUFFER_SIZE + 1])
{
	int	bytes_read;

	if (!stash)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(stash);
			return (NULL);
		}
		if (bytes_read == 0)
			break;
		buffer[bytes_read] = '\0';
		stash = help_free(stash, buffer);
		if (!stash)
			return (NULL);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	buffer [BUFFER_SIZE + 1];
	static char	*stash;
	char		*line;
	char		*next;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_file(fd, stash, buffer);
	if (!stash)
		return (NULL);
	line = get_line(stash);
	if (!line)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	next = shift_buffer(stash);
	free(stash);
	stash = next;
	return (line);
}

// int main(int argc, char **argv)
// {
	// int fd;
	// char *line;
// 
	// if (argc != 2)
	// {
		// printf("Usage: %s <file>\n", argv[0]);
		// return (1);
	// }
	// fd = open(argv[1], O_RDONLY);
	// /* if (fd < 0)
	// {
		// perror("Error opening file");
		// return (1);
	// } */
	// line = get_next_line(fd);
	// while (line)
	// {
		// printf("%s", line);
		// free(line);
		// line = get_next_line(fd);
	// }
	// close(fd);
	// return (0);
// }

int main(int argc, char **argv) {
	int fd = open("test_short.txt", O_RDONLY);
	int fd2 = 4;
	char *line;
	line = get_next_line(fd2);
	if (!line)
		printf("NULL\n");
	else
		printf("%s", line);
	free(line);
	close(fd);
}