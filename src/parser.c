/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:58:13 by hrother           #+#    #+#             */
/*   Updated: 2024/03/15 15:51:02 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_redirect(t_cmd *cmd, t_token *redirect)
{
	t_list *new_node;

	new_node = ft_lstnew(redirect);
	if (new_node == NULL)
		return (FAILURE);
	ft_lstadd_back(&cmd->redirects, new_node);
	return (SUCCESS);
}

int check_cmd(const t_cmd *cmd)
{
	if (cmd && cmd->bin && cmd->args && cmd->args[0])
		return (SUCCESS);
	log_msg(ERROR, "Syntax Error");
	return (FAILURE);
}

int	process_token(t_token *token, t_cmd **cmd, int *i_args)
{
	log_msg(DEBUG, "Processing token: type:%i value:%s", token->type,
		token->value);
	if (token->type == CMD)
	{
		(*cmd)->bin = token->value;
		(*cmd)->args[0] = token->value;
	}
	else if (token->type == ARG)
	{
		(*cmd)->args[*i_args] = token->value;
		(*i_args)++;
	}
	else if (token->type == R_IN || token->type == R_OUT
		|| token->type == R_APPEND || token->type == R_HEREDOC)
		return (add_redirect(*cmd, token));
	else if (token->type == PIPE)
	{
		if (check_cmd(*cmd) == FAILURE)
			return (FAILURE);
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
int	count_tokens(t_list *tokens, t_token_type type, t_token_type end)
{
	int		count;
	t_list	*current;

	count = 0;
	current = tokens;
	while (current != NULL)
	{
		if (type == 0 || ((t_token *)current->content)->type == type)
			count++;
		if (end != 0 && ((t_token *)current->content)->type == end)
			break ;
		current = current->next;
	}
	return (count);
}

t_cmd	*start_new_command(t_list **commands, int n_args)
{
	t_cmd	*new_command;
	t_list	*new_node;

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
	new_command->args[n_args] = NULL;
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
	int		n_args;
	int		i_args;

	commands = NULL;
	new_command = NULL;
	current_token = tokens;
	while (current_token)
	{
		if (new_command == NULL)
		{
			n_args = count_tokens(current_token, ARG, PIPE) + 1;
			new_command = start_new_command(&commands, n_args);
			if (new_command == NULL)
				return (ft_lstclear(&commands, free_cmd), NULL);
			i_args = 1;
		}
		if (process_token((t_token *)current_token->content, &new_command, &i_args) == FAILURE)
			return (ft_lstclear(&commands, free_cmd), NULL);
		current_token = current_token->next;
	}
	if (check_cmd(new_command) == FAILURE)
		return (ft_lstclear(&commands, free_cmd), NULL);
	return (commands);
}
