#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_parser{
	char **args;
	int flag_pipe;
	int a;
	int b;
} t_parser;

void	*ft_calloc(size_t count, size_t size);
int		ft_strlen(char *str);
char	*ft_strjoin_char(char *s1, char s2);
char *ft_quotes(char *line, int *a, char *tmp);
void ft_parser(char *line, t_parser *parser);
char	*ft_strdup(char *src);

#endif
