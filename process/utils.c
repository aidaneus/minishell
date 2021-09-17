/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbump <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 02:02:07 by gbump             #+#    #+#             */
/*   Updated: 2021/09/16 02:02:09 by gbump            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*add_signs(char *line, char *signs)
{
	int	i;

	i = -1;
	while (signs[++i])
	{
		line[i] = signs[i];
	}
	line[i] = '\0';
	return (line);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	find_equal(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	ft_isprint(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

int	ft_strncmp(const char *str1, const char *str2, unsigned int len)
{
	unsigned int	i;

	i = 0;
	while (i < len && str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	if (i != len)
		return ((unsigned char)str1[i] - (unsigned char)str2[i]);
	return (0);
}
