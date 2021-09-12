#include "../minishell.h"

char *put_pwd(char *all, int i)
{
    int j;
    char put[1024];

    j = -1;
	if (getcwd(put, sizeof(char) * 1024) == NULL)
		return (NULL);
    if (i == 6)
    {
        all = (char*)malloc(sizeof(char) * (8 + ft_strlen(put)));
        all = add_signs(all, "OLDPWD=");
        // all[0] = 'O';
        // all[1] = 'L';
        // all[2] = 'D';
        // all[3] = 'P';
        // all[4] = 'W';
        // all[5] = 'D';
        // all[6] = '=';
    }
    if (i == 3)
    {
        all = (char*)malloc(sizeof(char) * (5 + ft_strlen(put)));
        all = add_signs(all, "PWD=");
        // all[0] = 'P';
        // all[1] = 'W';
        // all[2] = 'D';
        // all[3] = '=';
    }
    while(put[++j] && j < ft_strlen(put))
    {
        all[++i] = put[j];
    }
    all[++i] = '\0';
    return (all);
}

void    find_chdir(t_parser *parser, int a)
{
    char mean[1024];
    int i;
    int j;
    int count;

    count = 0;
    if (a == 0)
    {
        i = 4;
        j = -1;
        while (parser->env[parser->len][++i])
            mean[++j] = parser->env[parser->len][i];
    }
    if (a == 1)
    {
        i = -1;
        while (parser->env[parser->len][++i])
        {
            if (parser->env[parser->len][i] == '/')
                count++;
        }
        i = 3;
        j = -1;
        while (count != 0)
        {
           mean[++j] = parser->env[parser->len][++i];
           if (parser->env[parser->len][i] == '/')
                count--;
        }
    }
    mean[++j] = '\0';
    chdir(mean);
}

int go_cd(t_parser *parser)
{
	int i;
	int j;

    parser->pwd1 = (char**)malloc(sizeof(char*) * 2);
    parser->pwd1[0] = put_pwd(parser->pwd1[0], 6);
   if (!parser->line[1])
   {
       i = 4;
       j = 3;
       parser->pwd1[1] = "HOME";
       check_export_2(parser, 1, parser->pwd1, 'c');
       find_chdir(parser, 0);
       parser->pwd1[1] = put_pwd(parser->pwd1[1], 3);
       check_export_2(parser, 0, parser->pwd1, 'c');
       check_export_2(parser, 1, parser->pwd1, 'c');
   }
   else if (parser->line[1][0] == '.' && parser->line[1][1] == '.' && ft_strlen(parser->line[1]) == 2)
   {
       parser->pwd1[1] = "PWD";
       check_export_2(parser, 1, parser->pwd1, 'c');
       find_chdir(parser, 1);
       parser->pwd1[1] = put_pwd(parser->pwd1[1], 3);
       check_export_2(parser, 0, parser->pwd1, 'c');
       check_export_2(parser, 1, parser->pwd1, 'c');
   }
    else if (chdir(parser->line[1]) == -1)
	{
        printf("%s %s %s%s\n", "bash:", "cd:", parser->line[1], ": No such file or directory");
        parser->what = 1;
		return (-1);
	}
    else
    {
        parser->pwd1[1] = put_pwd(parser->pwd1[1], 3);

        check_export_2(parser, 0, parser->pwd1, 'c');
        check_export_2(parser, 1, parser->pwd1, 'c');
    }
    free(parser->pwd1[0]);
    free(parser->pwd1[1]);
    free(parser->pwd1);
    return (0);
}