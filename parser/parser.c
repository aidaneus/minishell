/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhildred <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 23:51:46 by nhildred          #+#    #+#             */
/*   Updated: 2021/09/11 23:51:46 by nhildred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_counter(char *line)
{
	int	b;

	b = 0;
	while (*line)
	{
		if (*line != ' ' && (*(line + 1) == ' ' || *(line + 1) == '\0'))
			b++;
		line++;
	}
	return (b);
}

char	*check_if(char *line, int *a, char *tmp, t_parser *parser)
{
	if (line[*a] == 39 || line[*a] == 34)
	{
		tmp = ft_quotes(line, a, tmp, parser);
		(*a)++;
	}
	else if (line[*a] == '>')
		redirect(line, a, 1, parser);
	else if (line[*a] == '<')
		redirect(line, a, 2, parser);
	else if (line[*a] == '$')
		tmp = check_env_char(line, a, tmp, parser);
	else
	{
		tmp = ft_strjoin_char(tmp, line[*a]);
		(*a)++;
	}
	return (tmp);
}

char	**check_if_me(char **args, char **tmp, int *b)
{
	args[*b] = ft_strdup(*tmp);
	(*b)++;
	free(*tmp);
	*tmp = NULL;
	return (args);
}

void	check_pipe(char *line, int *a, t_parser *parser)
{
	int	b;
	int	count;

	count = 0;
	b = 0;
	skip_spaces(line, a);
	if (line[*a] == '|')
		check_error(line, a, parser, 2);
	while (line[b] != '\0')
	{
		if (line[b] == '|')
			count++;
		b++;
	}
	if (count != 0)
	{
		while (line[b] != '|')
			b--;
		while (*a <= b)
			(*a)++;
	}
}

char	**ft_parser(char *line, t_parser *parser)
{
	int		a;
	char	*tmp;

	a = 0;
	parser->b = 0;
	tmp = NULL;
	check_pipe(line, &a, parser);
	parser->line = (char **)calloc(sizeof(char *), (ft_counter(line) + 1));
	while (line[a] != '\0')
	{
		if (line[a] != ' ')
			tmp = check_if(line, &a, tmp, parser);
		else
		{
			if (tmp != NULL)
				parser->line = check_if_me(parser->line, &tmp, &parser->b);
			skip_spaces(line, &a);
		}
	}
	if (tmp)
		parser->line[parser->b] = ft_strdup(tmp);
	free(tmp);
	return (parser->line);
}
