/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkim <youkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 15:27:09 by youkim            #+#    #+#             */
/*   Updated: 2021/06/15 14:34:07 by youkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	where_newline(char *backup)
{
	int i;

	i = -1;
	while (backup[++i])
		if (backup[i] == '\n')
			return (i);
	return (-1);
}

int	pop_line(char **backup, char **line, int cut_where)
{
	char	*temp;

	(*backup)[cut_where] = '\0';
	*line = ft_strdup(*backup);
	if (!ft_strlen(*backup + cut_where + 1))
	{
		free(*backup);
		*backup = 0;
	}
	else
	{
		temp = ft_strdup(*backup + cut_where + 1);
		free(*backup);
		*backup = temp;
	}
	return (1);
}

int	result(char **backup, char **line)
{
	int	cut_where;

	if (*backup && (cut_where = where_newline(*backup)) >= 0)
		return (pop_line(backup, line, cut_where));
	else if (*backup)
	{
		*line = *backup;
		*backup = 0;
	}
	else
		*line = ft_strdup("");
	return (0);
}

int	get_next_line(int fd, char **line)
{
	int			len;
	int			cut_where;
	char		buffer[BUFFER_SIZE + 1];
	static char	*backup[OPEN_MAX];

	if ((fd < 0) || (line == 0) || (BUFFER_SIZE <= 0))
		return (-1);
	while ((len = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[len] = '\0';
		backup[fd] = ft_strjoin(backup[fd], buffer);
		if ((cut_where = where_newline(backup[fd])) >= 0)
			return (pop_line(&backup[fd], line, cut_where));
	}
	if (len < 0)
		return (-1);
	return (result(&backup[fd], line));
}
