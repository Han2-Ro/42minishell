/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:55:25 by hannes            #+#    #+#             */
/*   Updated: 2024/04/10 16:15:10 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_list *remove_env(t_list *envlst, const char *key)
{
    t_list *ret;

    if (envlst == NULL)
        return (NULL);
    envlst->next = remove_env(envlst->next, key);
    if (ft_strncmp(((t_env *)envlst->content)->key, key, ft_strlen(key)) == 0)
    {
        ret = envlst->next;
        free_env(envlst->content);
        free(envlst);
    }
    else
        ret = envlst;
    return(ret);
}

int builtin_unset(const t_cmd *cmd, t_list **envp)
{
    int i;
    
    i = 1;
    while (cmd->args[i] != NULL)
    {
        *envp = remove_env(*envp, cmd->args[i]);
        i++;
    }
    return (SUCCESS);
}
