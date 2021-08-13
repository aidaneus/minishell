#include "minishell.h"

// void errors() 
// {
//     char *a;

//     printf("%s: command not found\n", a);
//     printf("%s: No such file or directory\n", a);
// }

int ft_counter(char *line)
{
	int a;
	int b;

	a = 0;
	b = 0;
	// while (line[a] == ' ')
	// 	a++;
	while (line[a] != '\0' && line[a] != '|')
	{
		if (line[a] == ' ')
			b++;
		a++;
	}
	b++;
	return (b);
}

// void check_dollor(char *line, int *a, char *tmp)
// {
//     while (line[(*a)] != ' ' && line[*a] != '\0' && line[*a] != 34)
//     {
//         // отправить лайн на проверку в env и найти значение до '='
//         tmp = ft_strjoin_char(tmp, line[*a])
//         (*a)++;
//     }
// }

char *ft_quotes(char *line, int *a, char *tmp)
{
	char *save;

	save = NULL;
	save = tmp;
	if (line[*a] == 39)
	{
		(*a)++;
		while (line[*a] != 39)
			save = ft_strjoin_char(save, line[(*a)++]);
	}
	else if (line[*a] == 34)
	{
		(*a)++;
		while (line[*a] != 34)
		{
			// сделать расскрытие доллара $
			// if (line[*a] == '$')
            // {
            //     (*a)++;
			// 	check_dollor(line, a, tmp);
            // }
			// else
				save = ft_strjoin_char(save, line[(*a)++]);
		}
	}
	return (save);
}

char *check_if(char *line, int *a, char *tmp)
{
	if (line[*a] == 39 || line[*a] == 34) // проверка на '' и ""
		tmp = ft_quotes(line, a, tmp);
	// обработать редиректы
	// else if (line[*a] == '|')
	// 	printf("pipe");
	else
		tmp = ft_strjoin_char(tmp, line[*a]);
	(*a)++;
	return (tmp);
}

char **check_if_me(char **args, char **tmp, int *b)
{
	args[*b] = ft_strdup(*tmp);
	(*b)++;
	free(*tmp);
	*tmp = NULL;
	return (args);
}

void ft_parser(char *line, t_parser *parser)
{
	int a;
	char *tmp;

	a = 0;
	parser->b = 0;
	tmp = NULL;
	while (line[a] == ' ')
		a++;
	parser->args = (char **)ft_calloc(sizeof(char *), ft_counter(line));
	while (line[a] != '\0' && line[a] != '|')
	{
		if (line[a] != ' ')
			tmp = check_if(line, &a, tmp);
		else
		{
			parser->args = check_if_me(parser->args, &tmp, &parser->b);
			while (line[a] == ' ')
				a++;
		}
	}
	if (tmp)
		parser->args[parser->b] = ft_strdup(tmp);
	free(tmp);
}

int main(int argc, char **argv, char **envp)
{
	t_parser parser;
	char *line;
	int a;

	while (1)
	{
		a = 0;
		line = readline("minishell: ");
		if (line)
			add_history(line);
		ft_parser(line, &parser);
		printf("%s\n", parser.args[0]);
		// printf("%s\n", parser.args[1]);
		// printf("%s\n", parser.args[1]);
		// printf("%d\n", parser.b);
		while (a <= parser.b)
		{
			free(parser.args[a]);
			a++;
		}
		free(parser.args);
		free(line);
	}
	return (0);
}