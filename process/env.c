#include "../minishell.h"

void	env(char **env)
{
	int	i;

	i = 0;
	while (*env)
	{
		if (ft_strlen(env[0]) == 6)
			env++;
		if (*env[0] != '\0')
			printf ("%s\n", *env);
		env++;
	}
}
