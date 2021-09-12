#include "../minishell.h"

int unset(t_parser *parser)
{
	int i;

	i = -1;
	while (parser->line[++i])
	{
		check_export(parser, i, 'u');
	}
	if (i != 1)
		return (0);
	return (0);
}