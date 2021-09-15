/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbump <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 20:18:30 by gbump             #+#    #+#             */
/*   Updated: 2021/09/15 20:18:37 by gbump            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env(char **env, int oldpwd)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strlen(env[oldpwd]) == 6 && !env[oldpwd + 1] && i == oldpwd)
			break ;
		if (ft_strlen(env[oldpwd]) == 6 && env[oldpwd + 1] && i == oldpwd)
			env++;
		if (env[i][0] != '\0')
			printf ("%s\n", env[i]);
		i++;
	}
}
