/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbump <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 20:19:17 by gbump             #+#    #+#             */
/*   Updated: 2021/09/15 20:19:22 by gbump            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_minishell(t_parser *parser)
{
	if (!parser->line[1]
		|| (parser->line[1][0] == '0' && ft_strlen(parser->line[1]) == 1))
	{
		printf("%s\n", "exit");
		exit(0);
	}
	else if (parser->line[1][0] == '1' && ft_strlen(parser->line[1]) == 1)
	{
		printf("%s\n", "exit");
		exit(1);
	}
}
