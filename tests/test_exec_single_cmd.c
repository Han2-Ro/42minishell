#include "../minishell.h"
#include <stdio.h>

int	test_stdin_out(char **envp)
{
	t_cmd cmd = {
		.bin = "/bin/ls",
		.args = (char *[]){"ls", "-l", NULL},
		.envp = envp,
	};
	exec_single_cmd(cmd, STDIN_FILENO, STDOUT_FILENO);
	return (0);
}

int	test_filein_out(char **envp)
{
	int	fd_in;
	int	fd_out;

	t_cmd cmd = {
		.bin = "/bin/grep",
		.args = (char *[]){"grep", "test", NULL},
		.envp = envp,
	};
	fd_in = open("in", O_RDONLY);
	fd_out = open("out", O_WRONLY);
	exec_single_cmd(cmd, fd_in, fd_out);
	close(fd_in);
	close(fd_out);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	test_stdin_out(envp);
	test_filein_out(envp);
}