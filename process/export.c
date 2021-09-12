#include "../minishell.h"

t_parser export_create(char **envp, t_parser parser)
{
	int a;
	int b;
	int c;

	a = -1;
	b = 0;
	parser.export[0] = (char*)malloc(sizeof(char) * (6 + 1));
	parser.export[0] = add_signs(parser.export[0], "OLDPWD");
	parser.env[0] = (char*)malloc(sizeof(char) * (6 + 1));
	parser.env[0] = add_signs(parser.env[0], "OLDPWD");
	while (envp[++a])
	{
		b = 0;
		c = 0;
		parser.export[a+1] = (char*)malloc(sizeof(char) * (ft_strlen(envp[a]) + 3));//3
		parser.env[a+1] = (char*)malloc(sizeof(char) * (ft_strlen(envp[a]) + 1));//1
		while (envp[a][c] != '\0')
		{
			parser.export[a+1][b] = envp[a][c];
			parser.env[a+1][c] = envp[a][c];
			if (envp[a][c] == '=')
			{
				b++;
				parser.export[a+1][b] = '"';
			}
			if (envp[a][c+1] == '\0')
			{
				b++;
				parser.export[a+1][b] = '"';
			}
			b++;
			c++;
		}
		parser.export[a+1][b+1] = '\0';
		parser.env[a+1][c+1] = '\0';
	}
	return (parser);
}

int export_add(int a, t_parser *parser, char **line)
{
	int b;
	int c;
	int en;


	b = 0;
	c = 0;
	en = 0;
	if (parser->export[parser->len])
		free(parser->export[parser->len]);
	if (parser->env[parser->len])
		free(parser->env[parser->len]);
	parser->export[parser->len] = (char*)malloc(sizeof(char) * (ft_strlen(line[a]) + 3));
	parser->env[parser->len] = (char*)malloc(sizeof(char) * (ft_strlen(line[a]) + 1));
	while (line[a][c])
	{
		parser->export[parser->len][b] = line[a][c];
		parser->env[parser->len][en] = line[a][c];
		if (line[a][c] == '=')
		{
			b++;
			parser->export[parser->len][b] = '"';
		}
		if (line[a][c+1] == '\0' && b > c)
		{
			b++;
			parser->export[parser->len][b] = '"';
		}
		b++;
		c++;
		en++;
	}
	parser->export[parser->len][b] = '\0';
	parser->env[parser->len][en] = '\0';
	return (0);
}

int	export(t_parser *parser)
{
	int a;
	int i;

	a = 'A';
	i = 0;
    parser->len = 0;
	while (parser->env[parser->len])
		parser->len++;
	while (parser->line[++i])
	{
		check_export(parser, i, 'e');
	}
	if (i != 1)
		return (0);
	while (a != 'Z')
	{
		i = 0;
		while (parser->export[i])
		{
			if (parser->export[i][0] == a && parser->export[i][0] != '\0')
			{
				printf("%s", "declare -x ");
				printf("%s\n", parser->export[i]);
			}
			i++;
		}
		a++;
	}
	i = -1;
	while (parser->export[++i])
	{
		if (ft_isalpha(parser->export[i][0]) == 0 && parser->export[i][0] != '\0')
		{
			printf("%s", "declare -x ");
			printf("%s\n",parser->export[i]);
		}
	}
	a = 'a';
	while (a != 'z')
	{
		i = 0;
		while (parser->export[i])
		{
			if (parser->export[i][0] == a && parser->export[i][0] != '\0')
			{
				printf("%s", "declare -x ");
				printf("%s\n", parser->export[i]);
			}
			i++;
		}
		a++;
	}
	return (0);
}