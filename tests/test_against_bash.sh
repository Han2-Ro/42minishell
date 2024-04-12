#!/bin/bash

$@ > temp/bash.out
echo $@ | ./minishell > temp/minishell.out
diff temp/bash.out temp/minishell.out