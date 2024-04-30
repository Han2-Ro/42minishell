/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 21:59:46 by hrother           #+#    #+#             */
/*   Updated: 2024/04/30 19:48:52 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

/**
 * @brief Create a new list element
 * @deprecated use ft_lstnew instead
 */
t_list	*ft_lstnew_old(t_cmd *cmd)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content = cmd;
	new->next = NULL;
	return (new);
}

/**
 * @deprecated use ft_lstadd_back instead
 */
t_list	*ft_lstadd(t_list **lst, t_cmd *cmd)
{
	t_list	*new;
	t_list	*tmp;

	tmp = *lst;
	new = ft_lstnew_old(cmd);
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

/**
 * @deprecated use ft_lstclear instead
 */
void	destroy_list(t_list *lst)
{
	t_list	*tmp;

	log_msg(DEBUG, "destroying list");
	while (lst != NULL)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->content);
		free(tmp);
	}
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast((*lst));
	last->next = new;
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*next;

	current = *lst;
	while (current)
	{
		next = current->next;
		ft_lstdelone(current, del);
		current = next;
	}
	*lst = NULL;
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL)
		return ;
	del(lst->content);
	free(lst);
}

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

t_list	*ft_lstlast(t_list *lst)
{
	while (lst && lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	void	*content;
	t_list	*newlist;
	t_list	*node;

	if (!lst || !del || !f)
		return (NULL);
	newlist = NULL;
	while (lst)
	{
		content = f(lst->content);
		node = ft_lstnew(content);
		if (!node)
		{
			free(node);
			free(content);
			ft_lstclear(&newlist, del);
			return (NULL);
		}
		ft_lstadd_back(&newlist, node);
		lst = lst->next;
	}
	return (newlist);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

int	ft_lstsize(t_list *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}
/**
 * @brief Insert a list into another list
 */
void	ft_lstinsert(t_list *insert_after, t_list *list)
{
	t_list	*original_next;

	if (insert_after == NULL || list == NULL)
		return ;
	original_next = insert_after->next;
	insert_after->next = list;
	ft_lstlast(list)->next = original_next;
}

/**
 * @brief Seemlessly delete one node of a list

	* @brief Will not del anything if the the node to delete is not within the list (head)
 */
void	ft_lstrmvone(t_list **head, t_list *node, void (*del)(void *))
{
	t_list	*curr;

	if (*head == node)
	{
		*head = node->next;
		ft_lstdelone(node, del);
		return ;
	}
	curr = *head;
	while (curr->next != node && curr != NULL)
	{
		curr = curr->next;
	}
	if (curr->next == node)
	{
		curr->next = node->next;
		ft_lstdelone(node, del);
		return ;
	}
}
