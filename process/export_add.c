#include "../minishell.h"

static void add_free_and_malloc(t_parser *parser, char **line, int a, int c1)
{
	if (parser->export[parser->len])
		free(parser->export[parser->len]);
	if (parser->env[parser->len] && c1 == 'c')
		free(parser->env[parser->len]);
	parser->export[parser->len] = (char *)malloc(sizeof(char)
			* (ft_strlen(line[a]) + 3));
//	if (c1 == 'c')
	//	parser->env[parser->len] = (char *)malloc(sizeof(char)
		//		* (ft_strlen(line[a]) + 1));
}

int	export_add(int a, t_parser *parser, char **line, int c1)
{
	int	b;
	int	c;
	int en;

	b = 0;
	c = 0;
	en = 0;
	add_free_and_malloc(parser, line, a, c1);
	while (line[a][c])
	{
		parser->export[parser->len][b] = line[a][c];
		if (c1 == 'c' && line[a][0] == 'O')
			parser->env[parser->len] = ft_strdup1(line[a]);;
		if (c1 == 'c' && line[a][0] == 'P')
			parser->env[parser->len] = ft_strdup1(line[a]);
		//	parser->env[parser->len][en] = line[a][c];
		//parser->env[parser->len][en] = line[a][c];
		if (line[a][c] == '=')
			parser->export[parser->len][++b] = '"';
		if (line[a][c + 1] == '\0' && b > c)
			parser->export[parser->len][++b] = '"';
		b++;
		c++;
//		en++;
	}
	parser->export[parser->len][b] = '\0';
//	parser->env[parser->len][en] = '\0';
	return (0);
}
