/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monicaharutyunyan <monicaharutyunyan@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 20:57:21 by monicaharut       #+#    #+#             */
/*   Updated: 2022/05/17 13:52:09 by monicaharut      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*tatic;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	tatic = read_file(fd, tatic);
	if (!tatic)
		return (NULL);
	next_line = new_line(tatic);
	tatic = update_tatic(tatic);
	return (next_line);
}

char	*read_file(int fd, char *tatic)
{
	char	*temp;
	int		read_len;

	temp = (char *)malloc((BUFFER_SIZE + 1) + sizeof(char));
	if (!temp)
		return (NULL);
	read_len = 1;
	while (read_len != 0 && !ft_strchr(tatic, '\n'))
	{
		read_len = read(fd, temp, BUFFER_SIZE);
		if (read_len == -1)
		{
			free(temp);
			return (NULL);
		}
		temp[read_len] = '\0';
		tatic = ft_strjoin(tatic, temp);
	}
	free(temp);
	return (tatic);
}

char	*new_line(char *tatic)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!tatic[i])
		return (NULL);
	while (tatic[i] && tatic[i] != '\n')
		i++;
	line = (char *)malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (tatic[i] && tatic[i] != '\n')
	{
		line[i] = tatic[i];
		i++;
	}
	if (tatic[i] == '\n')
	{
		line[i] = tatic[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*update_tatic(char *tatic)
{
	size_t	i;
	size_t	j;
	char	*upd;

	i = 0;
	while (tatic[i] && tatic[i] != '\n')
		i++;
	if (!tatic[i])
	{
		free(tatic);
		return (NULL);
	}
	upd = (char *)malloc(sizeof(char) * (ft_strlen(tatic) - i + 1));
	if (!upd)
		return (NULL);
	i++;
	j = 0;
	while (tatic[i])
		upd[j++] = tatic[i++];
	upd[j] = '\0';
	free(tatic);
	return (upd);
}
