CC=cc
CFLAGS = -Wall -Wextra -Werror -g
SRC_DIR = src
OBJ_DIR = obj
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
NAME = minishell
RM = rm -rf

LIB = minishell.a

TEST_DIR = tests
TESTS = $(wildcard $(TEST_DIR)/*.c)
TESTBINS = $(patsubst $(TEST_DIR)/test_%.c, $(TEST_DIR)/bin/test_%, $(TESTS))
TEST_UTILS = $(TEST_DIR)/run_test.c #$(wildcard $(TEST_DIR)/utils/*.c)

$(LIB): $(OBJS)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(TEST_DIR)/bin:
	mkdir $@

$(TEST_DIR)/bin/%: $(TEST_DIR)/%.c $(LIB) $(TEST_DIR)/bin
	$(CC) $(CFLAGS) $< $(OBJS) -o $@

test: $(TESTBINS)
	for test in $(TESTBINS); do \
		$$test; \
	done 

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all