/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbump <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 01:26:22 by gbump             #+#    #+#             */
/*   Updated: 2021/09/16 01:26:26 by gbump            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup1(const char *str)
{
	int		i;
	int		j;
	char	*str1;

	i = 0;
	while (str[i])
	{
		i++;
	}
	str1 = (char *)malloc(sizeof(*str1) * (i + 1));
	if (!(str1))
	{
		return (NULL);
	}
	j = 0;
	while (j < i)
	{
		str1[j] = str[j];
		j++;
	}
	str1[j] = '\0';
	return (str1);
}

static void	rewrite_malloc(t_parser *parser, char **envp, int a)
{
	parser->export[a] = (char *)malloc(sizeof(char)
			* (ft_strlen(envp[a]) + 3));
	parser->env[a] = (char *)malloc(sizeof(char)
			* (ft_strlen(envp[a]) + 1));
}

int	rewrite_export(char **envp, t_parser *parser)
{
	int	a;
	int	b;
	int	c;

	a = -1;
	while (envp[++a])
	{
		b = 0;
		c = -1;
		rewrite_malloc(parser, envp, a);
		while (envp[a][++c] != '\0')
		{
			parser->export[a][b] = envp[a][c];
			parser->env[a][c] = envp[a][c];
			if (envp[a][c] == '=')
				parser->export[a][++b] = '"';
			if (envp[a][c + 1] == '\0')
				parser->export[a][++b] = '"';
			b++;
		}
		parser->export[a][b] = '\0';
		parser->env[a][c] = '\0';
	}
	return (a);
}

void	export_create(char **envp, t_parser *parser)
{
	parser->oldpwd = rewrite_export(envp, parser);
	parser->line = (char **)malloc(sizeof(char *));
	parser->line[0] = ft_strdup1("OLDPWD");
	unset(parser);
	free(parser->line[0]);
	free(parser->line);
	parser->export[parser->oldpwd] = (char *)malloc(sizeof(char) * (6 + 1));
	parser->export[parser->oldpwd]
		= add_signs(parser->export[parser->oldpwd], "OLDPWD");
	parser->env[parser->oldpwd] = (char *)malloc(sizeof(char) * (6 + 1));
	parser->env[parser->oldpwd]
		= add_signs(parser->env[parser->oldpwd], "OLDPWD");
}
