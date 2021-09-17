NAME = minishell

CC = gcc

FLAGS = -Wall -Wextra -Werror

INCLUDE = minishell.h


SRC = 	minishell.c \
		process/utils.c \
		process/export.c \
		process/cd.c \
		process/cd_directions.c \
		process/exit.c \
		process/echo.c \
		process/env.c \
		process/pwd.c \
		process/unset.c \
		process/process.c \
		process/export_create.c \
		process/export_add.c \
		process/export_print.c \
		process/check.c \
		process/utils_2.c \
		parser/parser.c \
		parser/parser_utils.c \
		parser/get_next_line.c \
		parser/get_next_line_utils.c \
		parser/env_char.c \
		parser/quotes.c \
		parser/heredoc.c \
		parser/parser_utils2.c \
		parser/redirects.c \
		parser/close_n_errors.c \

OBJ = $(SRC:c=o)
#OBJ = $(patsubst %.c, %.o, $(SRC))
all: $(NAME)

$(NAME): $(INCLUDE) $(SRC) $(OBJ)
	@echo "\n"
	@echo "\033[0;32mCompiling minishell..."
	@gcc $(FLAGS) $(SRC) -g -lreadline -L$(HOME)/.brew/opt/readline/lib -I$(HOME)/.brew/opt/readline/include -o $(NAME)
	@rm -rf minishell.dSYM
	@echo "\n\033[0mDone !"

%.o: %.c
	@printf "\033[0;33mGenerating minishell objects... %-33.33s\r" $@
	@${CC} ${CFLAGS} -c $< -o $@

clean:
	@echo "\033[0;31mCleaning libft..."
	@echo "\nRemoving binaries..."
	@rm -f $(OBJ)
	@echo "\033[0m"

fclean:
	@echo "\nDeleting objects..."
	@rm -f $(OBJ)
	@echo "\nDeleting executable..."
	@rm -f $(NAME)
	@echo "\033[0m"

re: fclean all

.PHONY: clean fclean re test norm