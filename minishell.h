/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbump <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 02:11:57 by gbump             #+#    #+#             */
/*   Updated: 2021/09/16 02:12:05 by gbump            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include "parser/get_next_line.h"
# include <termios.h>
# include <sys/types.h>
# include <dirent.h>

typedef struct s_parser{
	char	**env;
	char	*path;
	char	**path1;
	char	*usr_path;
	char	*usr_path1;
	char	*usr_path2;
	char	*usr_path3;
	char	**line;
	char	*put;
	int		what;
	char	**pwd1;
	int		oldpwd;
	char	**export;
	char	*itoa;
	int		flag_pipe;
	int		flag_heredoc;
	int		flag_redirect;
	int		flag_exit;
	int		i;
	int		j;
	int		a;
	int		b;
	int		len;
	int		last_cmd_rtn;
	int		oldstdout;
	int		fd2;
	int		fd;
	int		flag_close;
	int		flag;
	int		bb;
	int		cc;
	int		ll;
}			t_parser;

void	check_error(char *line, int *a, t_parser *parser, int n);
void	read_file(t_parser *parser, char *tmp);
char	**ft_split(char	const *s, char c);
char	*ft_itoa(int n, t_parser *parser);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
int		heredoc(char *delimeter);
char	*ft_strchr(const char *str, int s);
int		ft_strlen(char *str);
char	**ft_split(char	const *s, char c);
int		ft_strncmp(const char *str1, const char *str2, unsigned int len);
int		ft_isprint(int c);
int		export_add(int a, t_parser *parser, char **line, int c1);
void	export_create(char **envp, t_parser *parser);
int		ft_isalpha(int c);
int		check_export(t_parser *parser, int a, int c);
int		export(t_parser *parser);
int		find_equal(char *line);
int		go_cd(t_parser *parser);
char	*pwd(void);
int		check_export_2(t_parser *parser, int a, char **line, int c1);
char	**ft_memset(char **b, char *c, size_t len);
char	*add_signs(char *line, char *signs);
char	*pwd(void);
int		set_echo(char **line);
int		unset(t_parser *parser);
void	exit_minishell(t_parser *parser);
char	**ft_parser(char *line, t_parser *parser);
int		ft_parser_strlen(char *str);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strjoin_char(char *s1, char s2);
char	*check_env_char(char *line, int *a, char *tmp, t_parser *parser);
int		get_next_line(int fd, char **line);
char	*ft_quotes(char *line, int *a, char *tmp, t_parser *parser);
void	skip_spaces(char *line, int *a);
void	redirect(char *line, int *a, int num, t_parser *parser);
void	close_fd(t_parser *parser);
void	go_cd_empty(t_parser *parser);
void	go_cd_dot_dot(t_parser *parser);
void	go_cd_straight(t_parser *parser);
char	*put_pwd(char *all, int i);
void	find_chdir_1(t_parser *parser);
void	find_chdir_0(t_parser *parser);
int		ft_execve(t_parser *parser);
void	process(t_parser *parser);
void	export_a_to_z(t_parser *parser);
void	export_A_TO_Z(t_parser *parser);
void	export_not_alpha(t_parser *parser);
void	env(char **env, int oldpwd);
char	*ft_strdup1(const char *str);
void	sig_int(int flag);
char	*ft_strjoin1(char const *s1, char const *s2);

#endif
