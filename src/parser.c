/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:58:13 by hrother           #+#    #+#             */
/*   Updated: 2024/05/14 16:38:00 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	add_redirect(t_cmd *cmd, t_token *redirect)
{
	t_list	*new_node;

	new_node = ft_lstnew(redirect);
	if (new_node == NULL)
		return (FAILURE);
	ft_lstadd_back(&cmd->redirects, new_node);
	return (SUCCESS);
}

int	process_token(t_token *token, t_cmd **cmd)
{
	int	i;

	log_msg(DEBUG, "Processing token: type:%i value:%s", token->type,
		token->value);
	if (token->type == ARG || token->type == CMD)
	{
		i = 0;
		while ((*cmd)->args[i] != NULL)
			i++;
		(*cmd)->args[i] = token->value;
	}
	else if (token->type == R_IN || token->type == R_OUT
		|| token->type == R_APPEND || token->type == R_HEREDOC
		|| token->type == R_QUOTEDOC)
		return (add_redirect(*cmd, token));
	else if (token->type == PIPE)
	{
		if ((*cmd) == NULL || (*cmd)->args == NULL)
			return (log_msg(ERROR, "Syntax Error"), FAILURE);
		*cmd = NULL;
	}
	return (SUCCESS);
}

/**
 * @brief Count the number of tokens of a given type
 * @param tokens The list of tokens
 * @param type The type of token to count or 0 to count all tokens
 * @param end The type of token to count until (inclusive)
 * or 0 to count until the end of the list
 * @return The number of tokens counted
 */
int	count_args(t_list *tokens)
{
	int		count;
	t_list	*current;

	count = 0;
	current = tokens;
	while (current != NULL)
	{
		if (((t_token *)current->content)->type == ARG
			|| ((t_token *)current->content)->type == CMD)
			count++;
		if (((t_token *)current->content)->type == PIPE)
			break ;
		current = current->next;
	}
	return (count);
}

t_cmd	*start_new_command(t_list **commands, t_list *current_token)
{
	t_cmd	*new_command;
	t_list	*new_node;
	int		n_args;

	n_args = count_args(current_token);
	log_msg(DEBUG, "Starting new command with %i args", n_args);
	new_command = new_cmd(NULL, NULL);
	if (new_command == NULL)
		return (NULL);
	new_node = ft_lstnew(new_command);
	if (new_node == NULL)
		return (free(new_command), NULL);
	ft_lstadd_back(commands, new_node);
	new_command->args = (char **)malloc(sizeof(char *) * (n_args + 1));
	if (new_command->args == NULL)
		return (log_msg(ERROR, "malloc failed"), NULL);
	ft_bzero(new_command->args, (sizeof(char *)) * (n_args + 1));
	return (new_command);
}

/**
 * @brief Parse the tokens into a list of commands
 * @param tokens The list of tokens to parse
 * @return A list of commands or NULL on error
 */
t_list	*parse(t_list *tokens)
{
	t_list	*commands;
	t_list	*current_token;
	t_cmd	*new_command;

	commands = NULL;
	new_command = NULL;
	current_token = tokens;
	while (current_token)
	{
		if (new_command == NULL)
		{
			new_command = start_new_command(&commands, current_token);
			if (new_command == NULL)
				return (ft_lstclear(&commands, free_cmd), NULL);
		}
		if (process_token((t_token *)current_token->content,
				&new_command) == FAILURE)
			return (ft_lstclear(&commands, free_cmd), NULL);
		current_token = current_token->next;
	}
	if (new_command == NULL || new_command->args == NULL)
		return (ft_lstclear(&commands, free_cmd), log_msg(ERROR,
				"Syntax Error"), NULL);
	return (commands);
}
