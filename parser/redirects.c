/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhildred <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 23:22:30 by nhildred          #+#    #+#             */
/*   Updated: 2021/09/11 23:22:30 by nhildred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_red(char *line, int *a, t_parser *parser, int num)
{
	if (line[*a] == '>' && num == 1)
	{
		parser->flag_redirect = 1;
		(*a)++;
	}
	if (line[*a] == '<' && num == 2)
	{
		parser->flag_redirect = 1;
		(*a)++;
	}
}

void	red_output(char *line, int *a, char *tmp, t_parser *parser)
{
	parser->fd = 0;
	check_red(line, a, parser, 1);
	skip_spaces(line, a);
	check_error(line, a, parser, 1);
	if (parser->flag == 1)
		return ((void) NULL);
	while (line[*a] != ' ' && line[*a] != '\0')
		tmp = ft_strjoin_char(tmp, line[(*a)++]);
	if (parser->fd)
		close(parser->fd);
	if (parser->flag_redirect == 1)
		parser->fd = open(tmp, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		parser->fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	parser->oldstdout = dup(1);
	dup2(parser->fd, 1);
	close(parser->fd);
	free(tmp);
}

void	red_input(char *line, int *a, char *tmp, t_parser *parser)
{
	check_red(line, a, parser, 2);
	skip_spaces(line, a);
	check_error(line, a, parser, 1);
	if (parser->flag_exit == 1)
		return ((void) NULL);
	while (line[*a] != ' ' && line[*a] != '\0')
		tmp = ft_strjoin_char(tmp, line[(*a)++]);
	if (parser->line[0] != NULL)
	{
		parser->fd2 = open(tmp, O_RDONLY, 0644);
		close(parser->fd2);
		free(tmp);
		return ((void) NULL);
	}
	if (parser->flag_redirect == 1)
	{
		parser->flag_heredoc = heredoc(tmp);
		free(tmp);
		return ((void) NULL);
	}
	parser->fd2 = open(tmp, O_RDONLY, 0644);
	read_file(parser, tmp);
	free(tmp);
	close(parser->fd2);
}

void	redirect(char *line, int *a, int num, t_parser *parser)
{
	char	*tmp;

	tmp = NULL;
	(*a)++;
	parser->flag_redirect = 0;
	parser->flag_close = num;
	if (num == 1)
		red_output(line, a, tmp, parser);
	if (num == 2)
		red_input(line, a, tmp, parser);
	if (parser->flag_heredoc == 1)
		exit(0);
}
