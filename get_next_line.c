/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarapin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 18:33:24 by vsarapin          #+#    #+#             */
/*   Updated: 2017/12/15 18:33:30 by vsarapin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*s3;
	char		*tmp;
	size_t		i;
	size_t		j;

	j = 0;
	i = 0;
	while (s1[i])
		i += 1;
	while (s2[j])
		j += 1;
	if (!s1 || !s2 || !(s3 = (char *)malloc(sizeof(char) * (i + j + 1))))
		return (NULL);
	tmp = s3;
	while (*s1 != '\0')
		*tmp++ = *s1++;
	while (*s2 != '\0')
		*tmp++ = *s2++;
	*tmp = '\0';
	return (s3);
}

char	*ft_strdup(const char *s1)
{
	char		*s;
	size_t		i;

	i = 0;
	while (s1[i])
		i += 1;
	if (!(s = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = -1;
	while (s1[++i])
		s[i] = s1[i];
	s[i] = '\0';
	return (s);
}

int		check_line(char **array_of_fd, char **line)
{
	char			*tmp;
	char			*look_for_nextline;
	int				i;

	i = 0;
	look_for_nextline = *array_of_fd;
	while (look_for_nextline[i] != '\n')
		if (!look_for_nextline[i++])
			return (0);
	tmp = &look_for_nextline[i];
	*tmp = '\0';
	*line = ft_strdup(*array_of_fd);
	*array_of_fd = ft_strdup(tmp + 1);
	free(look_for_nextline);
	return (1);
}

int		read_from_file(int fd, char *buffer, char **array_of_fd, char **line)
{
	int				ret_value;
	char			*tmp;

	while ((ret_value = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[ret_value] = '\0';
		if (*array_of_fd)
		{
			tmp = *array_of_fd;
			*array_of_fd = ft_strjoin(tmp, buffer);
			free(tmp);
			tmp = NULL;
		}
		else
			*array_of_fd = ft_strdup(buffer);
		if (check_line(array_of_fd, line))
			break ;
	}
	if (ret_value < 0)
		return (-1);
	if (ret_value > 0)
		return (1);
	return (0);
}

int		get_next_line(int const fd, char **line)
{
	static char		*array_of_fd[4864];
	char			*buffer;
	int				ret_value;

	if (!line || (fd < 0 || fd >= 4864) || (read(fd, array_of_fd[fd], 0) < 0) \
		|| !(buffer = (char *)malloc(sizeof(char) * BUFF_SIZE + 1)))
		return (-1);
	if (array_of_fd[fd])
		if (check_line(&array_of_fd[fd], line))
			return (1);
	ret_value = read_from_file(fd, buffer, &array_of_fd[fd], line);
	free(buffer);
	if (ret_value != 0 || array_of_fd[fd] == NULL || array_of_fd[fd][0] == '\0')
	{
		if (!ret_value && *line)
			*line = NULL;
		return (ret_value);
	}
	*line = array_of_fd[fd];
	array_of_fd[fd] = NULL;
	return (1);
}
