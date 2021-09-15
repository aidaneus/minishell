/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbump <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 01:28:01 by gbump             #+#    #+#             */
/*   Updated: 2021/09/16 01:28:06 by gbump            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_echo(char **line)
{
	int	j;
	int	n;

	j = 1;
	n = 0;
	while (line[j] && (ft_strlen("-n") == ft_strlen(line[j]))
		&& ft_strncmp(line[j], "-n", ft_strlen(line[j])) == 0)
	{
		j++;
		n = 1;
	}
	while (line[j])
	{
		printf("%s", line[j]);
		if (line[j + 1] != '\0')
			printf("%s", " ");
		j++;
	}
	if (n == 0)
		printf("%c", '\n');
	return (0);
}
