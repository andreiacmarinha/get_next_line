/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andqueir <andqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:38:37 by andqueir          #+#    #+#             */
/*   Updated: 2025/11/20 18:25:13 by andqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	if (!buffer[i] || !buffer[i + 1])
		return (NULL); // nothing left after newline
	next = ft_calloc(ft_strlen(buffer) - i, sizeof(char));
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
	static char	buffer[MAX_FD][BUFFER_SIZE + 1];
	static char	*stash[MAX_FD];
	char		*line;
	char		*next;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash[fd])
	{
		stash[fd] = ft_calloc(1, sizeof(char));
		if (!stash[fd])
			return (NULL);
	}
	stash[fd] = read_file(fd, stash[fd], buffer[fd]);
	if (!stash[fd])
		return (NULL);
	line = get_line(stash[fd]);
	if (!line)
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	next = shift_buffer(stash[fd]);
	free(stash[fd]);
	stash[fd] = next;
	return (line);
}

/* int main(int argc, char **argv)
{
	int fd1, fd2;
	char *line1, *line2;

	if (argc != 3)
	{
		printf("Usage: %s <file1> <file2>\n", argv[0]);
		return (1);
	}
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[2], O_RDONLY);
	if (fd1 < 0 || fd2 < 0)
	{
		perror("Error opening file");
		return (1);
	}
	line1 = get_next_line(fd1);
	line2 = get_next_line(fd2);
	while (line1 || line2)
	{
		if (line1)
		{
			printf("fd1: %s", line1);
			free(line1);
			line1 = get_next_line(fd1);
		}
		if (line2)
		{
			printf("fd2: %s", line2);
			free(line2);
			line2 = get_next_line(fd2);
		}
	}
	close(fd1);
	close(fd2);
	return (0);
} */
