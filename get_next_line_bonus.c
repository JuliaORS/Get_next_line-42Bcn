/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 12:11:07 by julolle-          #+#    #+#             */
/*   Updated: 2023/04/12 20:49:54 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read(char *storage, char *buffer, int read_bytes)
{
	if (read_bytes == -1)
	{
		free (buffer);
		free (storage);
		return (NULL);
	}
	buffer[read_bytes] = '\0';
	if (read_bytes > 0)
		storage = ft_strjoin(storage, buffer);
	return (storage);
}

char	*ft_join_storage(int fd, char *storage)
{
	int		read_bytes;
	char	*buffer;

	read_bytes = 1;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
	{
		free (storage);
		return (NULL);
	}
	buffer[0] = '\0';
	while (read_bytes > 0 && ft_strchr(buffer, '\n') == 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		storage = ft_read(storage, buffer, read_bytes);
		if (!storage)
		{
			free (buffer);
			free (storage);
			return (NULL);
		}
	}
	free (buffer);
	return (storage);
}

char	*ft_line(char *storage)
{
	char	*line;
	int		i;
	int		lenl;

	i = 0;
	lenl = 0;
	if (storage[0] == '\0')
		return (NULL);
	while (storage[lenl] != '\n' && storage[lenl] != '\0')
		lenl++;
	if (storage[lenl] == '\n')
		line = malloc((lenl + 2) * sizeof(char));
	else
		line = malloc((lenl + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (storage[i] != '\n' && storage[i] != '\0')
	{
		line[i] = storage[i];
		i++;
	}
	if (storage[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*new_storage(char *storage)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	if (!storage)
		return (NULL);
	while (storage[i] != '\n' && storage[i] != '\0')
		i++;
	if (storage[i] == '\0')
	{
		free(storage);
		return (NULL);
	}
	else
	{
		temp = ft_strdup(storage + i + 1);
		if (!temp)
		{
			free(storage);
			return (NULL);
		}
	}
	free(storage);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*storage[1024] = {NULL};
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{	
		free (storage[fd]);
		storage[fd] = NULL;
		return (NULL);
	}
	if (!storage[fd] || (storage[fd] && !ft_strchr(storage[fd], '\n')))
		storage[fd] = ft_join_storage(fd, storage[fd]);
	if (!storage[fd])
	{
		free (storage[fd]);
		return (NULL);
	}
	line = ft_line(storage[fd]);
	if (!line)
	{
		free(storage[fd]);
		storage[fd] = NULL;
		return (NULL);
	}
	storage[fd] = new_storage(storage[fd]);
	return (line);
}

/*int	main(void)
{
	char	*line;
	int		fd_1;
	int		i;
	char	file[] = "document.txt";
	char *str;

	str = "hola";
	fd_1 = open(file, O_RDONLY);
	i = 1;
	printf("FILE: %s\n", file);
	while (i)
	{
		line = get_next_line(fd_1);
		if (!line)
			return (0);
		printf("Line %d, size: %zu: ->%s<-\n", i, strlen(line), line);
		free(line);
		i++;
	}
}*/