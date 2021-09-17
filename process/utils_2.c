/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbump <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 05:40:16 by gbump             #+#    #+#             */
/*   Updated: 2021/09/17 05:40:17 by gbump            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	cword(char const *s, char c)
{
	int	w;

	w = 0;
	while (*s)
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
			w++;
		s++;
	}
	return (w);
}

static int	wordl(char const *s, char c)
{
	int	l;

	l = 0;
	while (*s != c && *s)
	{
		l++;
		s++;
	}
	return (l);
}

static void	*freefunction(char **func, int w)
{
	int	i;

	i = 0;
	while (i < w)
	{
		free(func[i]);
		i++;
	}
	free(func);
	return (NULL);
}

static char	**put(char const *s, int w, char c, char **func)
{
	int		i;
	int		j;
	int		l;

	i = -1;
	while (++i < w)
	{
		while (*s == c)
			s++;
		l = wordl(s, c);
		func[i] = (char *)malloc(sizeof(char) * (l + 1));
		if (!(func[i]))
			return (freefunction(func, i));
		j = 0;
		while (j < l)
			func[i][j++] = *s++;
		func[i][j] = '\0';
	}
	func[i] = NULL;
	return (func);
}

char	**ft_split(char	const *s, char c)
{
	char	**func;
	int		w;

	if (!s)
		return (NULL);
	w = cword(s, c);
	func = (char **)malloc(sizeof(char *) * (w + 1));
	if (!(func))
		return (NULL);
	func = put(s, w, c, func);
	return (func);
}
