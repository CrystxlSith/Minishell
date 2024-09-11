/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:43:21 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/09/11 10:57:31 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_to_cmd(char *data, t_cmd *current)
{
	int	i;
	char	**new_str;

	i = 0;
	if (current->str)
	{
		while (current->str[i])
			i++;
	}
	new_str = malloc(sizeof(char *) * (i + 2));
	if (!new_str)
		return ;
	i = 0;
	while (current->str && current->str[i])
	{
		new_str[i] = current->str[i];
		i++;
	}
	new_str[i] = ft_strdup(data);
	new_str[i + 1] = NULL;
	free(current->str);
	current->str = new_str;
}

t_cmd	*parser(t_lexer **tokens)
{
	t_cmd	*head;
	t_cmd	*current;
	t_lexer	*tmp;
	int		i;

	i = 0;
	tmp = *tokens;
	init_cmd(&head, &current);
	if (!check_synthax_error(tmp))
	{	
		while (tmp)
		{
			if (tmp->type == E_CMD)
				add_to_cmd(tmp->data, current);
			else if (tmp->type == E_OPTIONS || tmp->type == E_ARG)
				add_to_cmd(tmp->data, current);
			else if (tmp->type == E_PIPE)
			{
				i++;
				current->index = i;
				current->next = create_new_cmd();
				current->next->prev = current;
				current = current->next;
			}
			else if (is_redirection(tmp->type))
				handle_redirection(tmp, current);
			tmp = tmp->next;
		}
	}
	return (head);
}