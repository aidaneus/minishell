/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhildred <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 22:59:47 by nhildred          #+#    #+#             */
/*   Updated: 2021/09/11 22:59:47 by nhildred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*func_if(char *line, int *a, char *tmp, t_parser *parser)
{
	if (parser->env[parser->i][parser->j] == '='
		&& (line[*a] == '\0' || line[*a] == ' '
		|| (line[*a] == 34 && parser->flag == 1)))
	{
		parser->j++;
		while (parser->env[parser->i][parser->j] != '\0')
		{
			tmp = ft_strjoin_char(tmp, parser->env[parser->i][parser->j]);
			parser->j++;
		}
	}
	else
	{
		while (parser->j > 0)
		{
			parser->j--;
			(*a)--;
		}
	}
	return (tmp);
}

char	*check_env_char(char *line, int *a, char *tmp, t_parser *parser)
{
	parser->i = -1;
	(*a)++;
	if (line[*a] == '?')
	{
		printf("%d\n", parser->what);
	}
	while ((line[*a] != ' ' && line[*a] != '\0') && parser->env[++parser->i])
	{
		parser->j = 0;
		if (parser->flag == 1 && line[*a] == 34)
			break ;
		while (parser->env[parser->i][parser->j] == line[*a]
			&& parser->env[parser->i][parser->j] != '=')
		{
			parser->j++;
			(*a)++;
		}
		tmp = func_if(line, a, tmp, parser);
	}
	while ((line[*a] != '\0' && line[*a] != ' '))
	{
		if (parser->flag == 1 && line[*a] == 34)
			break ;
		(*a)++;
	}
	return (tmp);
}
