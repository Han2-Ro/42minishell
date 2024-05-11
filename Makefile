CC=clang
CFLAGS = -Werror -Wall -Wextra -g #-fsanitize=address
RM = rm -rf

SRC_DIR = src
OBJ_DIR = obj
SRCS = $(wildcard $(SRC_DIR)/*.c)
SRCS += $(wildcard $(SRC_DIR)/execution/*.c)
SRCS += $(wildcard $(SRC_DIR)/builtins/*.c)
SRCS += $(wildcard $(SRC_DIR)/utils/*.c)
SRCS += $(wildcard $(SRC_DIR)/expander/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

NAME = minishell
LIB = libminishell.a

TEST_DIR = tests
TESTS = $(wildcard $(TEST_DIR)/test_*.c)
TESTBINS = $(patsubst $(TEST_DIR)/test_%.c, $(TEST_DIR)/bin/test_%, $(TESTS))
TEST_UTILS = $(wildcard $(TEST_DIR)/utils/*.c)

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	make -C ./libft CFLAGS="$(CFLAGS)" CC="$(CC)"
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L. -L./libft -lft -lreadline

$(LIB): $(OBJ_DIR) $(OBJS)
	make -C ./libft
	ar rcs $@ $(OBJS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/builtins
	mkdir -p $(OBJ_DIR)/execution
	mkdir -p $(OBJ_DIR)/utils
	mkdir -p $(OBJ_DIR)/expander

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

$(TEST_DIR)/bin:
	mkdir $@

$(TEST_DIR)/bin/%: $(TEST_DIR)/%.c $(LIB) $(TEST_DIR)/bin
	$(CC) $(CFLAGS) $< -o $@ -L. -lminishell -lreadline -L./libft -lft

test: CFLAGS += -DLOG_LEVEL=DEBUG
test: $(TESTBINS)
	./$(TEST_DIR)/setup.sh; \
	exit_code=0; \
	for test in $(TESTBINS); do \
		$$test || exit_code=1; \
	done; \
	./$(TEST_DIR)/test_against_bash.sh || exit_code=1;\
	exit $$exit_code

clean:
	make clean -C ./libft
	$(RM) $(OBJ_DIR)

fclean: clean
	make fclean -C ./libft
	$(RM) $(NAME)
	$(RM) $(LIB)

re: fclean all

.PHONY: all clean fclean re test