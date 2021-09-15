#include "../minishell.h"

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
			if (envp[a][c] == '\0')
				parser->export[a][++b] = '"';
			b++;
		}
		parser->export[a][b + 1] = '\0';
		parser->env[a][c + 1] = '\0';
	}
	return (a);
}

t_parser	export_create(char **envp, t_parser parser)
{
	parser.oldpwd = rewrite_export(envp, &parser);
	parser.export[parser.oldpwd] = (char *)malloc(sizeof(char) * (6 + 1));
	parser.export[parser.oldpwd] = add_signs(parser.export[parser.oldpwd], "OLDPWD");
	parser.env[parser.oldpwd] = (char *)malloc(sizeof(char) * (6 + 1));
	parser.env[parser.oldpwd] = add_signs(parser.env[parser.oldpwd], "OLDPWD");
	return (parser);
}