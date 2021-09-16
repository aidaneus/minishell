/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhildred <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 02:21:49 by nhildred          #+#    #+#             */
/*   Updated: 2021/09/16 02:21:49 by nhildred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

static	int	check(unsigned int n)
{
	unsigned int	a;

	a = 1;
	while (n >= 10)
	{
		n /= 10;
		a++;
	}
	return (a);
}

unsigned int	check_if_itoa(int n, int num)
{
	if (num == 1)
	{
		if (n < 0)
			return (-n);
		else
			return (n);
	}
	if (num == 2)
	{
		if (n < 0)
			return (1);
		else
			return (0);
	}
	return (0);
}

char	*ft_itoa(int n, t_parser *parser)
{
	unsigned int	b;
	unsigned int	c;
	unsigned int	d;

	d = 0;
	c = check_if_itoa(n, 1);
	b = check(c);
	parser->itoa = (char *)malloc(sizeof(char) * b + 1 + check_if_itoa(n, 2));
	if (!(parser->itoa))
		return (NULL);
	if (n < 0)
	{
		parser->itoa[d] = '-';
		b++;
	}
	d = b - 1;
	while (c >= 10)
	{
		parser->itoa[d] = c % 10 + 48;
		c /= 10;
		d--;
	}
	parser->itoa[d] = c % 10 + 48;
	parser->itoa[b] = '\0';
	return (parser->itoa);
}
