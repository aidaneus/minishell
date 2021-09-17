/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_n_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhildred <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 22:55:49 by nhildred          #+#    #+#             */
/*   Updated: 2021/09/16 22:55:49 by nhildred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_fd(t_parser *parser)
{
	if (parser->flag_close == 1)
	{
		if (parser->oldstdout)
		{
			dup2(parser->oldstdout, 1);
			close(parser->oldstdout);
		}
	}
	if (parser->flag_close == 2 && parser->flag_exit != 1
		&& parser->flag_redirect != 1)
		close(parser->fd2);
}

void	check_error(char *line, int *a, t_parser *parser, int n)
{
	if (n == 1)
	{
		parser->flag_exit = 0;
		if (line[*a] == '\0')
		{
			parser->what = 258;
			printf("bash: syntax error near unexpected token `newline'\n");
			parser->flag_exit = 1;
		}
	}
	if (n == 2)
	{
		printf("bash: syntax error near unexpected token `|'\n");
		parser->what = 127;
		return ((void ) NULL);
	}
}
