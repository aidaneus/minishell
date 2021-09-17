/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhildred <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 02:10:36 by nhildred          #+#    #+#             */
/*   Updated: 2021/09/16 02:10:36 by nhildred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	process_heredoc(char *delimiter)
{
	char	*line;
	int		fd;

	line = NULL;
	fd = open(".heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	unlink(".heredoc");
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("> ");
		if (line == NULL || !ft_strncmp(line, delimiter, ft_strlen(line) + 1))
			break ;
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	if (line == NULL)
	{
		printf("\033[A");
		printf("> warning: here-document is delimited by EOF\n");
		exit(0);
	}
	free(line), close(fd);
	return (1);
}

int	heredoc(char *delimeter)
{
	pid_t	pid;
	int		status;
	int		flag;
	int		res;

	flag = 0;
	status = 0;
	pid = fork();
	if (pid < 0)
	{
		printf("Error\n");
		return (71);
	}
	else if (pid == 0)
		flag = process_heredoc(delimeter);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			res = WEXITSTATUS(status);
	}
	return (flag);
}
