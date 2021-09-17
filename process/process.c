/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbump <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 20:15:14 by gbump             #+#    #+#             */
/*   Updated: 2021/09/17 05:35:01 by gbump            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	process_extra_1(t_parser *parser)
{
	if (parser->line[0][0] == 'p' && parser->line[0][1] == 'w'
		&& parser->line[0][2] == 'd' && parser->line[0][3] == '\0')
	{
		pwd();
		return (1);
	}
	else if (parser->line[0][0] == 'e' && parser->line[0][1] == 'c'
			&& parser->line[0][2] == 'h' && parser->line[0][3] == 'o'
			&& ft_strlen(parser->line[0]) == 4)
	{
		set_echo(parser->line);
		return (1);
	}
	return (0);
}

static int	process_extra_2(t_parser *parser)
{
	if (parser->line[0][0] == 'u' && parser->line[0][1] == 'n'
			&& parser->line[0][2] == 's' && parser->line[0][3] == 'e'
			&& parser->line[0][4] == 't' && ft_strlen(parser->line[0]) == 5)
	{
		unset(parser);
		return (1);
	}
	else if (parser->line[0][0] == 'c' && parser->line[0][1] == 'd'
			&& ft_strlen(parser->line[0]) == 2)
	{
		go_cd(parser);
		return (1);
	}
	else if (parser->line[0][0] == 'e' && parser->line[0][1] == 'x'
			&& parser->line[0][2] == 'i' && parser->line[0][3] == 't'
			&& parser->line[0][4] == '\0')
	{
		exit_minishell(parser);
		return (1);
	}
	return (0);
}

static int	process_extra_3(t_parser *parser)
{
	if (parser->line[0][0] == 'e' && parser->line[0][1] == 'n'
			&& parser->line[0][2] == 'v' && parser->line[0][3] == '\0')
	{
		if (parser->line[1])
		{
			printf("%s %s%s\n", "env:",
				parser->line[1], ": No such file or directory");
			parser->what = 127;
			return (1);
		}
		env(parser->env, parser->oldpwd);
		return (1);
	}
	else if (parser->line[0][0] == 'e' && parser->line[0][1] == 'x'
			&& parser->line[0][2] == 'p' && parser->line[0][3] == 'o'
			&& parser->line[0][4] == 'r' && parser->line[0][5] == 't'
			&& ft_strlen(parser->line[0]) == 6)
	{
		export(parser);
		return (1);
	}
	return (0);
}

void	process(t_parser *parser)
{
	int	a;

	parser->what = 0;
	if (process_extra_1(parser) != 1 && process_extra_2(parser) != 1
		&& process_extra_3(parser) != 1)
	{
		a = -1;
		parser->path = ft_strjoin1("/", parser->line[0]);
		parser->path1 = ft_split(getenv("PATH"), ':');
		parser->what = ft_execve(parser);
		free(parser->path);
		while (parser->path1[++a])
			free(parser->path1[a]);
		free(parser->path1);
	}
}
