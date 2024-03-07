/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:58:13 by hrother           #+#    #+#             */
/*   Updated: 2024/03/07 22:43:45 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	process_token(t_token token, t_cmd **cmd, int *i_args)
{
	log_msg(DEBUG, "Processing token: type:%i value:%s", token.type, token.value);
	if (token.type == CMD)
		(*cmd)->bin = token.value;
	else if (token.type == ARG)
	{
		(*cmd)->args[*i_args] = token.value;
		(*i_args)++;
	}
	else if (token.type == R_IN)
		ft_lstadd_back(&(*cmd)->in, ft_lstnew(new_redir(token.value)));
	else if (token.type == R_OUT)
		ft_lstadd_back(&(*cmd)->out, ft_lstnew(new_redir(token.value)));
	else if (token.type == R_APPEND)
		log_msg(ERROR, "R_APPEND not yet implemented: skipping token");
	else if (token.type == R_HEREDOC)
		log_msg(ERROR, "R_HEREDOC not yet implemented: skipping token");
	else if (token.type == PIPE)
		*cmd = NULL;
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

t_cmd	*start_new_command(t_list **commands, int n_args, char **envp)
{
	t_cmd	*new_command;

	log_msg(DEBUG, "Starting new command with %i args", n_args);
	new_command = new_cmd(NULL, NULL, envp);
	if (new_command == NULL)
		return (NULL);
	ft_lstadd_back(commands, ft_lstnew(new_command));
	new_command->args = (char **)malloc(sizeof(char *) * (n_args + 1));
	if (new_command->args == NULL)
		return (log_msg(ERROR, "malloc failed"), NULL);
	new_command->args[n_args] = NULL;
	return (new_command);
}

/**
 * @brief Parse the tokens into a list of commands
 * @param tokens The list of tokens to parse
 * @return A list of commands that can be executed or NULL on error
 */
t_list	*parse(t_list *tokens, char **envp)
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
			n_args = count_tokens(current_token, ARG, PIPE);
			new_command = start_new_command(&commands, n_args, envp);
			if (new_command == NULL)
				return (ft_lstclear(&commands, free_cmd), NULL);
			i_args = 0;
		}
		process_token(*(t_token *)current_token->content, &new_command,
			&i_args);
		current_token = current_token->next;
	}
	return (commands);
}
