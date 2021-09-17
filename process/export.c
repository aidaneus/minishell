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

char	*ft_strjoin1(char const *s1, char const *s2)
{
	int		b;
	int		c;
	char	*d;

	if (!s1 || !s2)
		return (NULL);
	b = ft_strlen((char *)s1);
	c = ft_strlen((char *)s2);
	d = (char *)malloc(sizeof(char) * (b + c + 1));
	if (!(d))
		return (NULL);
	c = -1;
	while (s1[++c])
		d[c] = s1[c];
	c = 0;
	while (s2[c])
	{
		d[b] = s2[c];
		b++;
		c++;
	}
	d[b] = '\0';
	return (d);
}

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
