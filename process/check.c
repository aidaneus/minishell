/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbump <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 02:03:04 by gbump             #+#    #+#             */
/*   Updated: 2021/09/16 02:03:06 by gbump            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	arg_exported(t_parser *parser, int a, char **line, int c1)
{
	if (parser->ll == ft_strlen(line[a]) && find_equal(line[a]) == -1)
	{
		if (c1 == 'u')
		{
			free(parser->export[parser->cc]);
			free(parser->env[parser->cc]);
			parser->export[parser->cc] = "\0";
			parser->env[parser->cc] = "\0";
			return (-2);
		}
		parser->len = parser->cc;
		return (-2);
	}
	return (0);
}

static int	arg_change(t_parser *parser, int a, char **line, int c1)
{
	if (((parser->ll == find_equal(line[a]))
			&& find_equal(line[a]) != -1) && c1 != 'u')
	{
		parser->len = parser->cc;
		export_add(a, parser, line, c1);
		return (-3);
	}
	return (0);
}

static void	check_str(t_parser *parser, char **line, int a)
{
	while (parser->export[parser->cc][parser->bb])
	{
		if (parser->export[parser->cc][parser->bb] == line[a][parser->bb])
			parser->ll++;
		else
			parser->ll--;
		if (parser->export[parser->cc][parser->bb + 1] == '=')
			break ;
		parser->bb++;
	}
}

int	check_export_2(t_parser *parser, int a, char **line, int c1)
{
	parser->cc = -1;
	while (parser->export[++parser->cc])
	{
		parser->bb = 0;
		parser->ll = 0;
		check_str(parser, line, a);
		if (arg_exported(parser, a, line, c1) == -2)
			return (-2);
		if (arg_change(parser, a, line, c1) == -3)
			return (-3);
	}
	if (c1 != 'u')
	{
		parser->len = parser->cc;
		export_add(a, parser, line, c1);
	}
	return (0);
}

int	check_export(t_parser *parser, int a, int c1)
{
	int	b;
	int	l;

	l = 0;
	b = 0;
	while (parser->line[a][b])
	{
		if (ft_isalpha(parser->line[a][0]) == 0 && parser->line[a][0] != '_')
		{
			printf("%s %s %s%s%s%s\n", "bash:", "export:", "'",
				parser->line[a], "'", ": not a valid identifier");
			parser->what = 1;
			return (-1);
		}
		if (parser->line[a][b + 1] == '=')
			break ;
		b++;
	}
	return (check_export_2(parser, a, parser->line, c1));
}
