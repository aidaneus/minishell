#include "../minishell.h"

void	exit_minishell(t_parser *parser)
{
	if (!parser->line[1]
		|| (parser->line[1][0] == '0' && ft_strlen(parser->line[1]) == 1))
	{
		printf("%s\n", "exit");
		exit(0);
	}
	else if (parser->line[1][0] == '1' && ft_strlen(parser->line[1]) == 1)
	{
		printf("%s\n", "exit");
		exit(1);
	}
}
