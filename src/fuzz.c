#include "../includes/minishell.h"
#include <stdint.h>

int	LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{
	t_evars	evars;
	char	line[Size + 1];

	evars.tty = 0;
	evars.status = 0;
	evars.envp = ft_lstnew(new_env(ft_strdup("PATH"),
				ft_strdup("/bin:/usr/bin:/usr/local/bin")));
	ft_lstadd_back(&evars.envp, ft_lstnew(new_env(ft_strdup("HOME"),
				ft_strdup("/home/user"))));
	ft_lstiter(evars.envp, &print_env);
	if (Size == 0)
		return (0);
	ft_strlcpy(line, (char *)Data, Size + 1);
	process_line(line, &evars);
	ft_lstclear(&evars.envp, free_env);
	return (0);
}

/*
int	main(void) {
  uint8_t Data[100];
  size_t Size;

  Size = 10;
  ft_strlcpy((char *)Data, "sf%s§1asdg*d", Size);
  LLVMFuzzerTestOneInput(Data, Size);
  return (0);
}
*/