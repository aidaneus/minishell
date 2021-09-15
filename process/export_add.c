#include "../minishell.h"

static void add_free_and_malloc(t_parser *parser, char **line, int a)
{
	if (parser->export[parser->len])
		free(parser->export[parser->len]);
	if (parser->env[parser->len])
		free(parser->env[parser->len]);
	parser->export[parser->len] = (char *)malloc(sizeof(char)
			* (ft_strlen(line[a]) + 3));
	parser->env[parser->len] = (char *)malloc(sizeof(char)
			* (ft_strlen(line[a]) + 1));
}

int	export_add(int a, t_parser *parser, char **line)
{
	int	b;
	int	c;
	int	en;

	b = 0;
	c = 0;
	en = 0;
	add_free_and_malloc(parser, line, a);
	while (line[a][c])
	{
		parser->export[parser->len][b] = line[a][c];
		parser->env[parser->len][en] = line[a][c];
		if (line[a][c] == '=')
			parser->export[parser->len][++b] = '"';
		if (line[a][c + 1] == '\0' && b > c)
			parser->export[parser->len][++b] = '"';
		b++;
		c++;
		en++;
	}
	parser->export[parser->len][b] = '\0';
	parser->env[parser->len][en] = '\0';
	return (0);
}
