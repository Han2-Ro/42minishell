#include "../includes/minishell.h"
#include <stdint.h>

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  t_evars *evars;
  evars->tty = 0;
  evars->status = 0;
  evars->envp = ft_lstnew(new_env(ft_strdup("PATH"), ft_strdup("/bin:/usr/bin:/usr/local/bin")));
  ft_lstadd_back(&evars->envp, ft_lstnew(new_env(ft_strdup("HOME"), ft_strdup("/home/user"))));
  process_line(Data, evars);
  return 0;
}