#include "../minishell.h"

char *pwd(void)
{
	char new_pwd[1024];

	if (getcwd(new_pwd, sizeof(char) * 1024) == NULL)
	{
		return (NULL);
	}
	printf ("%s\n", new_pwd);
	return (NULL);
}