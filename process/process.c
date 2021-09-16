/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbump <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 20:15:14 by gbump             #+#    #+#             */
/*   Updated: 2021/09/15 20:16:54 by gbump            ###   ########.fr       */
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
	return (0);
}

static int	process_extra_3(t_parser *parser)
{
	if (parser->line[0][0] == 'e' && parser->line[0][1] == 'x'
			&& parser->line[0][2] == 'i' && parser->line[0][3] == 't'
			&& parser->line[0][4] == '\0')
	{
		exit_minishell(parser);
		return (1);
	}
	else if (parser->line[0][0] == 'e' && parser->line[0][1] == 'n'
			&& parser->line[0][2] == 'v' && parser->line[0][3] == '\0')
	{
		if (parser->line[1][0])
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

	if (process_extra_1(parser) != 1 && process_extra_2(parser) != 1
		&& process_extra_3(parser) != 1)
	{
		a = -1;
		if ((parser->line[0][0] == '.' && parser->line[0][1] == '/') || (parser->line[0][0] == '/'))
			parser->path = ft_strdup(parser->line[0]);
		else
		{
			parser->path = (char *)malloc(sizeof(char)
					* (6 + ft_strlen(parser->line[0])));
			parser->path = add_signs(parser->path, "/bin/");
			while (parser->line[0][++a])
				parser->path[a + 5] = parser->line[0][a];
			parser->path[a + 5] = '\0';
			a = -1;
			parser->usr_path = (char *)malloc(sizeof(char)
					* (6 + 4 + ft_strlen(parser->line[0])));
			parser->usr_path  = add_signs(parser->usr_path, "/usr/bin/");
			while (parser->line[0][++a])
				parser->usr_path[a + 9] = parser->line[0][a];
			parser->usr_path [a + 9] = '\0';
		}
	//	printf("%s\n", parser->path);
	//	printf("%s\n", parser->usr_path);
		parser->what = ft_execve(parser);
		if ((parser->line[0][0] == '.' && parser->line[0][1] == '/') || (parser->line[0][0] == '/'))
			free(parser->path);
		else
		{
		 	free(parser->path);
			free(parser->usr_path);		
		}
	}
}
