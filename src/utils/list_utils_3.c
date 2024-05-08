/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:58:34 by hrother           #+#    #+#             */
/*   Updated: 2024/05/07 15:58:50 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
