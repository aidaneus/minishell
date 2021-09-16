/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhildred <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 23:53:52 by nhildred          #+#    #+#             */
/*   Updated: 2021/09/11 23:53:52 by nhildred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_parser_strlen(char *str)
{
	int	a;

	a = 0;
	if (!str)
		return (0);
	while (str[a])
		a += 1;
	return (a);
}

void	*ft_calloc(size_t count, size_t size)
{
	char			*a;
	unsigned int	b;
	unsigned int	c;

	c = 0;
	b = count * size;
	a = malloc(b);
	if (!a)
		return (NULL);
	while (b--)
	{
		a[c] = 0;
		c++;
	}
	return (a);
}

char	*ft_strjoin_char(char *s1, char s2)
{
	int		i;
	char	*k;

	k = (char *)malloc(sizeof(char) * (ft_parser_strlen(s1) + 2));
	if (k == NULL)
		return (NULL);
	i = 0;
	if (s1 != NULL)
	{
		while (s1[i])
		{
			k[i] = s1[i];
			i++;
		}
	}
	k[i] = s2;
	k[++i] = '\0';
	if (s1 != NULL)
		free(s1);
	return (k);
}

void	skip_spaces(char *line, int *a)
{
	while (line[*a] == ' ')
		(*a)++;
}

void	read_file(t_parser *parser, char *tmp)
{
	int		output;
	char	*line_gnl;

	if (parser->fd2 == -1)
	{
		printf("bash: %s: No such file or directory\n", tmp);
		parser->what = 1;
		return ((void ) NULL);
	}
	output = get_next_line(parser->fd2, &line_gnl);
	while (output > 0)
	{
		printf("%s\n", line_gnl);
		free(line_gnl);
		output = get_next_line(parser->fd2, &line_gnl);
	}
	printf("%s\n", line_gnl);
	free(line_gnl);
}
