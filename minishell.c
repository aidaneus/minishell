#include "minishell.h"

int ft_execve(t_parser *parser)
{
	int status;
	pid_t pid;
	int i = 0;

	pid = fork();
	if (pid == 0)
	{
		if (execve(parser->path, parser->line, parser->env) == -1)
		{
			close_fd(parser);
			printf("%s %s%s\n", "bash:", parser->line[0], ": command not found");
			exit(127);
		}
	}
	else
	{
		 waitpid(pid, &status, 0);
		if (WIFEXITED(status))
    		i = WEXITSTATUS(status);
	}
	return (i);
}

void process(t_parser *parser)
{
	//int p = 0;
	//parser->what = p; 
	//if (!parser->what)
	//	parser->what = 9;
	if (parser->line[0][0] == 'p' && parser->line[0][1] == 'w' && parser->line[0][2] == 'd' && parser->line[0][3] == '\0')
		pwd();
	else if (parser->line[0][0] == 'e' && parser->line[0][1] == 'n' && parser->line[0][2] == 'v' && parser->line[0][3] == '\0')
		env(parser->env);
	else if (parser->line[0][0] == 'e' && parser->line[0][1] == 'c' && parser->line[0][2] == 'h' && parser->line[0][3] == 'o' && ft_strlen(parser->line[0]) == 4)
		set_echo(parser->line);
	else if (parser->line[0][0] == 'e' && parser->line[0][1] == 'x' && parser->line[0][2] == 'p' && parser->line[0][3] == 'o' 
			&& parser->line[0][4] == 'r' && parser->line[0][5] == 't' && ft_strlen(parser->line[0]) == 6)
			export(parser);
	else if (parser->line[0][0] == 'u' && parser->line[0][1] == 'n' && parser->line[0][2] == 's' && parser->line[0][3] == 'e' 
			&& parser->line[0][4] == 't' && ft_strlen(parser->line[0]) == 5)
			unset(parser);
	else if (parser->line[0][0] == 'c' && parser->line[0][1] == 'd' && ft_strlen(parser->line[0]) == 2)
		go_cd(parser);
	else if (parser->line[0][0] == 'e' && parser->line[0][1] == 'x' && parser->line[0][2] == 'i' && parser->line[0][3] == 't' && parser->line[0][4] == '\0')
		exit_minishell(parser);
	else
	{
		//	pid_t pid;
			 int a = -1;
			 parser->path = (char*)malloc(sizeof(char) * (6 + ft_strlen(parser->line[0])));
			parser->path = add_signs(parser->path, "/bin/");
			 while (parser->line[0][++a])
			 {
				parser->path[a+5] = parser->line[0][a];
			 }
			 parser->path[a+5] = '\0';
			 parser->what = ft_execve(parser);
			 //printf("%d\n", parser->what);
			//  pid = fork();
			//  if (pid == 0)
			// {
			// 	if (execve(parser->path, parser->line, parser->env) == -1)
			// 	{
			// 		close_fd(parser);
			//  		printf("%s %s%s\n", "bash:", parser->line[0], ": command not found");
			// 		exit(1);
			// 	}
			//  }
			//  else
			//  {
			// 	int status;
			//  	waitpid(pid, &status, 0);
			//  }
			 free(parser->path);
	}
}

void    ft_putstr_fd(char *s, int fd)
{
    int i;
    i = 0;
    if (s == NULL)
        return ;
    while (s[i] != '\0')
    {
        write(fd, &s[i], 1);
        i++;
    }
}

void    sig_int()
{
   printf("\n");
   rl_on_new_line();
    // rl_replace_line("", 0);	
    rl_redisplay();
	// struct termios	term;
	// tcgetattr(0, &term);
	// 	term.c_lflag &= ~(ECHO);
	// 	term.c_lflag &= ~(ICANON);
	// 	tcsetattr(0, TCSANOW, &term);
	// 	tcgetattr(0, &term);
	// 	term.c_lflag = 0x2020010d;
	// 	tcsetattr(0, TCSANOW, &term);
	// 	// rl_replace_line();
	// 	write(1, "\n", 1);
	// 	rl_on_new_line();
	// 	rl_redisplay();
}

int main(int argc, char *argv[], char **envp)
{
	t_parser parser;
	char *line1;
	int a;
	int b;

	parser.what = 0; 
	a = -1;
	b = 0;
	if (!argc || !argv)
		exit_minishell(&parser);
	parser.env = (char**)malloc(sizeof(char*) * 1024);
	parser.export = (char**)malloc(sizeof(char*) * 1024);
	parser = export_create(envp, parser);
	while (1)
	{
		a = 0;
		signal(SIGINT, &sig_int);
		signal(SIGQUIT, SIG_IGN);
		line1 = readline("\033[35mminishell: \033[0;32m");// \033[00m
		// printf("\033[A");
		if (line1)
			add_history(line1);
		if (!line1)
        {
			printf("\033[A"); 
    		printf("\033[35mminishell: \033[0;32mexit\n");
    		exit(0);
        }
		parser.line = ft_parser(line1, &parser);
		if (parser.line[0])
			process(&parser);
		close_fd(&parser);
		while (parser.line[a])
		{
			free(parser.line[a]);
			a++;
		}
		free(parser.line);
		free(line1);
	}
	return (0);
}