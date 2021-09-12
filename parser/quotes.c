/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhildred <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 23:11:43 by nhildred          #+#    #+#             */
/*   Updated: 2021/09/11 23:11:43 by nhildred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_quotes(char *line, int *a, char *tmp, t_parser *parser)
{
	char	*save;

	save = NULL;
	save = tmp;
	if (line[*a] == 39)
	{
		(*a)++;
		while (line[*a] != 39 && line[*a] != '\0')
			save = ft_strjoin_char(save, line[(*a)++]);
	}
	else if (line[*a] == 34)
	{
		(*a)++;
		while (line[*a] != 34 && line[*a] != '\0')
		{
			if (line[*a] == '$')
			{
				parser->flag = 1;
				save = check_env_char(line, a, save, parser);
			}
			else
				save = ft_strjoin_char(save, line[(*a)++]);
		}
	}
	return (save);
}
