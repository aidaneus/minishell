#include "../minishell.h"

char *add_signs(char *line, char *signs)
{
	int i;

	i = -1;
	while (signs[++i])
	{
		line[i] = signs[i];
	}
	line[i] = '\0';
	return (line);
}

int		ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int find_equal(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int check_export_2(t_parser *parser, int a, char **line, int c1)
{
	int b;
	int c;
	int l;

	l = 0;
	c = -1;
	while (parser->export[++c])
	{
		b = 0;
		l = 0;
		while (parser->export[c][b])
		{
			if (parser->export[c][b] == line[a][b])
				l++;
			else
				l--;
			if (parser->export[c][b+1] == '=')
				break ;
			b++;
		}
		if (l == ft_strlen(line[a]) && find_equal(line[a]) == -1)
		{
			if (c1 == 'u')
			{
				free(parser->export[c]);
				free(parser->env[c]);
				parser->export[c] = "\0";
				parser->env[c] = "\0";
				return (-2);
			}
			if (c1 == 'e')
				printf("%s\n", "argument already exported");
			parser->len = c;
			return (-2);
		}
		else if (((l == find_equal(line[a])) && find_equal(line[a]) != -1) && c1 != 'u')
		{
			if (c1 == 'e')
				printf("%s\n", "changing the argument");
			parser->len = c;
			export_add(a, parser, line);
			return (-3);
		}
	}
	if (c1 != 'u')
	{
		parser->len = c;
		export_add(a, parser, line);
	}
	return (0);
}

int check_export(t_parser *parser, int a, int c1)
{
	int b;
	int l;

	l = 0;
	b = 0;
	while (parser->line[a][b])
	{
		if (ft_isalpha(parser->line[a][0]) == 0 && parser->line[a][0] != '_')
		{
			printf("%s %s %s%s%s%s\n", "bash:", "export:" ,"'", parser->line[a], "'", ": not a valid identifier");
			parser->what = 1;
			return (-1);
		}
		if (parser->line[a][b + 1] == '=')
			break ;
		b++;
	}
	return (check_export_2(parser, a, parser->line, c1));
}

int		ft_isprint(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

int		ft_strncmp(const char *str1, const char *str2, unsigned int len)
{
	unsigned int i;

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