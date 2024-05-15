CC=clang
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf

SRC_DIR = src
OBJ_DIR = obj
SRCS = src/lexer_1.c \
src/lexer_2.c \
src/log.c \
src/loop.c \
src/main.c \
src/parser.c \
src/print_structs.c \
src/signal.c \
src/builtins/cd.c \
src/builtins/echo.c \
src/builtins/env.c \
src/builtins/exec_buitin.c \
src/builtins/exit.c \
src/builtins/export_1.c \
src/builtins/export_2.c \
src/builtins/pwd.c \
src/builtins/unset.c \
src/execution/execute_cmd.c \
src/execution/execute_cmd_list.c \
src/execution/get_bin.c \
src/execution/heredoc.c \
src/execution/redirects.c \
src/expander/expander.c \
src/expander/handle_dollar.c \
src/expander/handle_quote.c \
src/expander/split_token.c \
src/utils/environment_1.c \
src/utils/environment_2.c \
src/utils/free_utils.c \
src/utils/list_utils_1.c \
src/utils/list_utils_2.c \
src/utils/list_utils_3.c \
src/utils/utils.c \
src/utils/vstrjoin.c \
src/error/errprintf.c \
src/error/errprint_c.c \
src/error/errprint_i.c \
src/error/errprint_s.c \
src/utils/read_next_line.c

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

NAME = minishell

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	make -C ./libft
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L. -L./libft -lft -lreadline


$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/builtins
	mkdir -p $(OBJ_DIR)/execution
	mkdir -p $(OBJ_DIR)/utils
	mkdir -p $(OBJ_DIR)/expander
	mkdir -p $(OBJ_DIR)/error

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	make clean -C ./libft
	$(RM) $(OBJ_DIR)

fclean: clean
	make fclean -C ./libft
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re test