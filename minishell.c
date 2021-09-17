/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbump <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 20:12:53 by gbump             #+#    #+#             */
/*   Updated: 2021/09/17 05:47:07 by gbump            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bin(t_parser *parser)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (parser->path1[i])
	{
		if (execve(ft_strjoin(parser->path1[i], parser->path),
				parser->line, parser->env) == -1)
			a++;
		i++;
	}
	if (a == i)
	{
		if (execve(parser->line[0], parser->line, parser->env) == -1)
		{
			close_fd(parser);
			printf("%s %s%s\n", "bash:", parser->line[0], ": command not found");
			exit(127);
		}
	}
}

int	ft_execve(t_parser *parser)
{
	int		status;
	pid_t	pid;
	int		i;

	i = 0;
	pid = fork();
	if (pid == 0)
		bin(parser);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			i = WEXITSTATUS(status);
	}
	return (i);
}

void	sig_int(int flag)
{
	int	stat_loc;

	wait(&stat_loc);
	if (stat_loc == flag)
	{
		if (flag == SIGINT)
		{
			write(1, "\n", 1);
			rl_on_new_line();
		}
	}
	else if (flag == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	parse_and_proc(t_parser *parser)
{
	char			*line1;
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(0, TCSANOW, &term);
	signal(SIGINT, &sig_int);
	signal(SIGQUIT, SIG_IGN);
	line1 = readline("\033[35mminishell: \033[0;32m");
	if (!line1)
	{
		printf("\033[A");
		printf("\033[35mminishell: \033[0;32mexit\n");
		exit(0);
	}
	add_history(line1);
	parser->line = ft_parser(line1, parser);
	if (parser->line[0])
		process(parser);
	free(line1);
}

int	main(int argc, char *argv[], char **envp)
{
	t_parser	parser;
	int			a;

	if (!argc || !argv)
		exit_minishell(&parser);
	a = -1;
	parser.what = 0;
	parser.env = (char **)malloc(sizeof(char *) * 1024);
	parser.export = (char **)malloc(sizeof(char *) * 1024);
	export_create(envp, &parser);
	while (1)
	{
		parse_and_proc(&parser);
		close_fd(&parser);
		a = -1;
		while (parser.line[++a])
			free(parser.line[a]);
		free(parser.line);
	}
	return (0);
}
