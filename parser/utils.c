#include "minishell.h"

int		ft_strlen(char *str)
{
	int a;

	a = 0;
	if (!str)   //важная проверка для tmp в парсере
		return (0);
	while (str[a])
		a += 1;
	return (a);
}

char	*ft_strjoin_char(char *s1, char s2)
{
	int		i;
	char	*k;
	k = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 2));
	if (k == NULL)
		return (NULL);
	i = 0;
	if (s1 != NULL)
	{
		while (s1[i])
		{
			k[i] = s1[i];
			i++;
		}
	}
	k[i] = s2;
	k[++i] = '\0';
	if (s1 != NULL)
		free(s1);
	return (k);
}

void	*ft_calloc(size_t count, size_t size)
{
	char			*a;
	unsigned int	b;
	unsigned int	c;

	c = 0;
	b = count * size;
	if (!(a = malloc(b)))
		return (NULL);
	while (b--)
	{
		a[c] = 0;
		c++;
	}
	return (a);
}

char	*ft_strdup(char *src)
{
	char	*cpy;
	int		a;
	int		b;

	a = 0;
	b = 0;
	while (src[b])
		b += 1;
	if (!src || !(cpy = (char*)malloc(sizeof(char) * b + 1)))
		return (NULL);
	while (a < b)
	{
		cpy[a] = src[a];
		a++;
	}
	cpy[a] = '\0';
	return (cpy);
}