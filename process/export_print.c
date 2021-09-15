#include "../minishell.h"

void export_a_to_z(t_parser *parser)
{
	int a;
	int i;

	a = 'a';
	while (a != 'z')
	{
		i = 0;
		while (parser->export[i])
		{
			if (parser->export[i][0] == a && parser->export[i][0] != '\0')
				printf("%s%s\n", "declare -x ", parser->export[i]);
			i++;
		}
		a++;
	}
}

void export_A_TO_Z(t_parser *parser)
{
	int a;
	int i;

	a = 'A';
	i = 0;
	while (a != 'Z')
	{
		i = 0;
		while (parser->export[i])
		{
			if (parser->export[i][0] == a && parser->export[i][0] != '\0')
				printf("%s%s\n", "declare -x ", parser->export[i]);
			i++;
		}
		a++;
	}
}

void export_not_alpha(t_parser *parser)
{
	int i;

	i = -1;
	while (parser->export[++i])
	{
		if (ft_isalpha(parser->export[i][0]) == 0
			&& parser->export[i][0] != '\0')
			printf("%s%s\n", "declare -x ", parser->export[i]);
	}
}