/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_directions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbump <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 04:21:38 by gbump             #+#    #+#             */
/*   Updated: 2021/09/12 04:21:42 by gbump            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	go_cd_empty(t_parser *parser)
{
	int	i;
	int	j;

	i = 4;
	j = 3;
	parser->pwd1[1] = "HOME";
	check_export_2(parser, 1, parser->pwd1, 'c');
	find_chdir_0(parser);
	parser->pwd1[1] = put_pwd(parser->pwd1[1], 3);
	check_export_2(parser, 0, parser->pwd1, 'c');
	check_export_2(parser, 1, parser->pwd1, 'c');
}

void	go_cd_dot_dot(t_parser *parser)
{
	parser->pwd1[1] = "PWD";
	check_export_2(parser, 1, parser->pwd1, 'c');
	find_chdir_1(parser);
	parser->pwd1[1] = put_pwd(parser->pwd1[1], 3);
	check_export_2(parser, 0, parser->pwd1, 'c');
	check_export_2(parser, 1, parser->pwd1, 'c');
}

void	go_cd_straight(t_parser *parser)
{
	parser->pwd1[1] = put_pwd(parser->pwd1[1], 3);
	check_export_2(parser, 0, parser->pwd1, 'c');
	check_export_2(parser, 1, parser->pwd1, 'c');
}
