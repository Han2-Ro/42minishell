#!/bin/bash
FAIL_COUNT=0
RUN_DIR=temp
mkdir -p $RUN_DIR

function test {
    echo "Test: $1"
    echo -e "$1" | bash > $RUN_DIR/bash.out 2> $RUN_DIR/bash.err
    exit_bash=$?
    echo -e "$1" | ./minishell > $RUN_DIR/minishell.out 2> $RUN_DIR/minishell.err
    exit_minishell=$?
    DIFF=$(diff $RUN_DIR/bash.out $RUN_DIR/minishell.out)
    if [ "$DIFF" != "" ]; then
        echo "stdout diff:"
        echo $DIFF
        FAIL_COUNT=$((FAIL_COUNT+1))
    fi
    DIFF=$(diff $RUN_DIR/bash.err $RUN_DIR/minishell.err)
    if [ "$DIFF" != "" ]; then
        # error message may differ
        if [ $(cat $RUN_DIR/bash.err | wc -l) != $(cat $RUN_DIR/minishell.err | wc -l) ]; then
            echo "stderr diff:"
            echo $DIFF
            FAIL_COUNT=$((FAIL_COUNT+1))
        fi
    fi
    if [ $exit_bash != $exit_minishell ]; then
        echo "exit code diff:"
        echo "bash: $exit_bash"
        echo "minishell: $exit_minishell"
        FAIL_COUNT=$((FAIL_COUNT+1))
    fi
}

test 'nocmd'
test 'cd .. \n pwd'
test 'ls -l | grep d| wc -l'
test 'cat << EOF\nhello\nEOF'
test 'cat << EOF\n$HOME\nhello\nEOF'
test 'export a="echo hi"\n$a "<d"|cat -e'
test 'cat 1\t2   3'
test 'no_cmd\necho $?aaa'
test 'echo $"HOME"$USER'
#test 'export a="aa\'bb"\necho $a'
exit $FAIL_COUNT