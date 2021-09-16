/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbump <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 04:21:13 by gbump             #+#    #+#             */
/*   Updated: 2021/09/12 04:21:20 by gbump            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

char	*put_pwd(char *all, int i)
{
	int		j;
	char	put[1024];

	j = -1;
	if (getcwd(put, sizeof(char) * 1024) == NULL)
		return (NULL);
	if (i == 6)
	{
		all = (char *)malloc(sizeof(char) * (8 + ft_strlen(put)));
		all = add_signs(all, "OLDPWD=");
	}
	if (i == 3)
	{
		all = (char *)malloc(sizeof(char) * (5 + ft_strlen(put)));
		all = add_signs(all, "PWD=");
	}
	while (put[++j] && j < ft_strlen(put))
	{
		all[++i] = put[j];
	}
	all[++i] = '\0';
	return (all);
}

void	find_chdir_1(t_parser *parser)
{
	char	mean[1024];
	int		i;
	int		j;
	int		count;

	count = 0;
	i = -1;
	while (parser->env[parser->len][++i])
	{
		if (parser->env[parser->len][i] == '/')
			count++;
	}
	i = 3;
	j = -1;
	while (count != 0)
	{
		mean[++j] = parser->env[parser->len][++i];
		if (parser->env[parser->len][i] == '/')
			count--;
	}
	mean[++j] = '\0';
	chdir(mean);
}

void	find_chdir_0(t_parser *parser)
{
	char	mean[1024];
	int		i;
	int		j;

	i = 4;
	j = -1;
	while (parser->env[parser->len][++i])
		mean[++j] = parser->env[parser->len][i];
	mean[++j] = '\0';
	chdir(mean);
}

int	go_cd(t_parser *parser)
{
	parser->pwd1 = (char **)malloc(sizeof(char *) * 2);
	parser->pwd1[0] = put_pwd(parser->pwd1[0], 6);
	if (!parser->line[1])
		go_cd_empty(parser);
	else if (parser->line[1][0] == '.'
			&& parser->line[1][1] == '.' && ft_strlen(parser->line[1]) == 2)
		go_cd_dot_dot(parser);
	else if (chdir(parser->line[1]) == -1)
	{
		printf("%s %s %s%s\n", "bash:", "cd:",
			parser->line[1], ": No such file or directory");
		parser->what = 1;
		if (parser->pwd1[0])
			free(parser->pwd1[0]);
		if (parser->pwd1)
			free(parser->pwd1);
		return (-1);
	}
	else
		go_cd_straight(parser);
	free(parser->pwd1[0]);
	free(parser->pwd1[1]);
	free(parser->pwd1);
	return (0);
}
