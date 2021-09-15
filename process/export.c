/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbump <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 01:19:28 by gbump             #+#    #+#             */
/*   Updated: 2021/09/16 01:19:32 by gbump            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export(t_parser *parser)
{
	int	i;

	i = 0;
	parser->len = 0;
	while (parser->env[parser->len])
		parser->len++;
	while (parser->line[++i])
		check_export(parser, i, 'e');
	if (i != 1)
		return (0);
	export_A_TO_Z(parser);
	export_not_alpha(parser);
	export_a_to_z(parser);
	return (0);
}
