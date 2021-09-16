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

static int		cword(char const *s, char c)
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

static int		wordl(char const *s, char c)
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

static void		*freefunction(char **func, int w)
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

static char		**put(char const *s, int w, char c, char **func)
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
		if (!(func[i] = (char *)malloc(sizeof(char) * (l + 1))))
			return (freefunction(func, i));
		j = 0;
		while (j < l)
			func[i][j++] = *s++;
		func[i][j] = '\0';
	}
	func[i] = NULL;
	return (func);
}

char			**ft_split(char	const *s, char c)
{
	char	**func;
	int		w;

	if (!s)
		return (NULL);
	w = cword(s, c);
	if (!(func = (char **)malloc(sizeof(char *) * (w + 1))))
		return (NULL);
	func = put(s, w, c, func);
	return (func);
}

char	*ft_strjoin1(char const *s1, char const *s2)
{
	int		b;
	int		c;
	char	*d;

	if (!s1 || !s2)
		return (NULL);
	b = ft_strlen((char *)s1);
	c = ft_strlen((char *)s2);
	if (!(d = (char *)malloc(sizeof(char) * (b + c + 1))))
		return (NULL);
	c = 0;
	while (s1[c])
	{
		d[c] = s1[c];
		c++;
	}
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
