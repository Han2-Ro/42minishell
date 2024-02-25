/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 21:59:46 by hrother           #+#    #+#             */
/*   Updated: 2024/02/10 15:58:24 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

t_list	*ft_lstnew(t_cmd *cmd)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->cmd = cmd;
	new->next = NULL;
	return (new);
}

t_list	*ft_lstadd(t_list **lst, t_cmd *cmd)
{
	t_list	*new;
	t_list	*tmp;

	tmp = *lst;
	new = ft_lstnew(cmd);
	if (new == NULL)
		return (NULL);
	if (tmp == NULL)
	{
		*lst = new;
		return (*lst);
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	return (*lst);
}

void	destroy_list(t_list *lst)
{
	t_list	*tmp;

	printf("destroying list\n");
	while (lst != NULL)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->cmd);
		free(tmp);
	}
}