/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhildred <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 18:00:24 by nhildred          #+#    #+#             */
/*   Updated: 2020/12/23 14:06:21 by nhildred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	new_line(char **str, char **line, int a)
{
	char	*copy;

	copy = ft_substr(*str, (unsigned int)a + 1, ft_strlen(*str));
	if (copy == NULL)
	{
		free(*line);
		return (-1);
	}
	free(*str);
	*str = copy;
	if (*str[0] == '\0')
	{
		free(*str);
		*str = NULL;
	}
	return (a);
}

int	liner(char **str, char **line, int r)
{
	int	a;
	int	f;

	a = 0;
	f = 1;
	while ((*str)[a] != '\n' && (*str)[a] != '\0')
		a++;
	if (r == 0 && (ft_strchr(*str, '\n') == NULL))
		f = 0;
	*line = ft_substr(*str, 0, a);
	if ((*str)[a] == '\n')
	{
		if (new_line(str, line, a) == -1)
			return (-1);
	}
	else
	{
		free(*str);
		*str = NULL;
	}
	return (f);
}

int	ft_read(char **str, char **line, int r)
{
	int	a;

	if (r < 0)
	{
		free(*str);
		return (-1);
	}
	else if (r == 0 && *str == NULL)
	{
		*line = ft_strdup("");
		return (0);
	}
	else
	{
		a = liner(str, line, r);
		if (a == -1 && *str != NULL)
			free(*str);
		return (a);
	}
}

int	get_next_line(int fd, char **line)
{
	static char	*str[1024];
	char		buf[BUFFER_SIZE + 1];
	int			r;

	if (fd < 0 || line == NULL || BUFFER_SIZE < 1)
		return (-1);
	r = read(fd, &buf, BUFFER_SIZE);
	while (r > 0)
	{
		buf[r] = '\0';
		if (str[fd] == NULL)
			str[fd] = ft_strdup(buf);
		else
			str[fd] = ft_strjoin(str[fd], buf);
		if (str[fd] == NULL)
			return (-1);
		if (ft_strchr(str[fd], '\n'))
			break ;
	}
	return (ft_read(&str[fd], line, r));
}
