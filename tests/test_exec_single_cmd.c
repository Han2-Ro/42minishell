#include "../minishell.h"
#include <stdio.h>

int	test_stdin_out(char **envp)
{
	int	pid;

	t_cmd cmd = {
		.bin = "/bin/ls",
		.args = (char *[]){"ls", "-l", NULL},
		.envp = envp,
	};
	pid = exec_single_cmd(cmd, STDIN_FILENO, STDOUT_FILENO);
	waitpid(pid, NULL, 0);
	return (SUCCESS);
}

int	test_filein_out(char **envp)
{
	int	fd_in;
	int	fd_out;
	int	pid;

	t_cmd cmd = {
		.bin = "/bin/grep",
		.args = (char *[]){"grep", "test", NULL},
		.envp = envp,
	};
	fd_in = open("in", O_RDONLY);
	fd_out = open("out", O_WRONLY);
	pid = exec_single_cmd(cmd, fd_in, fd_out);
	close(fd_in);
	close(fd_out);
	waitpid(pid, NULL, 0);
	return (SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	printf("\n-------- %s --------\n", argv[0]);
	printf("\ntest_stdin_out\n");
	test_stdin_out(envp);
	printf("\ntest_filein_out\n");
	test_filein_out(envp);
	printf("------------ done ------------\n");
}