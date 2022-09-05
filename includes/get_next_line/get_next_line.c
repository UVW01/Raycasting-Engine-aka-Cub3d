/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <mnaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 15:59:35 by mnaimi            #+#    #+#             */
/*   Updated: 2022/08/11 15:28:01 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* -------------------------------------------------------------------------- */

static char	*final_step(char **the_rest, char **line_ptr)
{
	void	*dummy_ptr;

	if (!*line_ptr)
		return (NULL);
	if (ft_strchr(*line_ptr, '\n') && (ft_strchr(*line_ptr, '\n') + 1))
	{
		dummy_ptr = *line_ptr;
		*the_rest = ft_strdup(ft_strchr(*line_ptr, '\n') + 1);
		if (!*the_rest)
			return (NULL);
		ft_bzero(ft_strchr(*line_ptr, '\n'), \
			ft_strlen(ft_strchr(*line_ptr, '\n')));
		*line_ptr = ft_strdup(*line_ptr);
		if (!*line_ptr)
			return (NULL);
		free(dummy_ptr);
	}
	return (*line_ptr);
}

/* -------------------------------------------------------------------------- */

static char	*read_file(char **line_ptr, int fd, int buffer_size)
{
	void	*dummy_ptr;
	char	*buf;
	int		count;

	buf = (char *)ft_calloc((buffer_size + 1), sizeof(char));
	if (!buf)
		return (NULL);
	while (!ft_strchr(*line_ptr, '\n'))
	{
		count = read(fd, buf, buffer_size);
		if (count <= 0)
		{
			if (!**line_ptr)
				return (free(buf), free(*line_ptr), NULL);
			return (free(buf), *line_ptr);
		}
		dummy_ptr = *line_ptr;
		*line_ptr = ft_strjoin(*line_ptr, buf);
		if (!*line_ptr)
			return (NULL);
		free(dummy_ptr);
		ft_bzero(buf, buffer_size + 1);
	}
	return (free(buf), *line_ptr);
}

/* -------------------------------------------------------------------------- */

char	*get_next_line(int fd, int buffer_size)
{
	static char	*the_rest;
	char		*line;

	if (buffer_size <= 0 || fd < 0)
	{
		if (the_rest)
		{
			free(the_rest);
			the_rest = 0;
		}
		return (NULL);
	}
	if (the_rest)
	{
		line = ft_strdup(the_rest);
		free(the_rest);
		the_rest = 0;
	}
	else
		line = (char *)ft_calloc(1, sizeof(char));
	if (!line)
		return (NULL);
	line = read_file(&line, fd, buffer_size);
	line = final_step(&the_rest, &line);
	return (line);
}
