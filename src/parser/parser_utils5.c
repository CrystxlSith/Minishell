/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:54:37 by agiliber          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/10/21 10:41:22 by agiliber         ###   ########.fr       */
=======
/*   Updated: 2024/10/18 15:10:03 by jopfeiff         ###   ########.fr       */
>>>>>>> 0f2fb0de3936a87fb5364b63e3d089244d360d71
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	new_heredoc(t_cmd *cmd, t_heredoc *new_hdc)
{
	t_heredoc	*last_hdc;

	new_hdc->next = NULL;
	new_hdc->prev = NULL;
	if (cmd->hdc_count == 0)
		cmd->hdc = new_hdc;
	else
	{
		last_hdc = cmd->hdc;
		while (last_hdc->next)
			last_hdc = last_hdc->next;
		last_hdc->next = new_hdc;
		new_hdc->prev = last_hdc;
	}
	cmd->hdc_count++;
}

void	fill_heredoc(t_lexer **token, t_cmd *current, t_heredoc *new_hdc)
{
	int	i;

	i = 0;
	if ((*token)->type == E_REDIR_DEL && (*token)->next)
	{
		while (current->str != NULL && current->str[i])
			i++;
		while (current->next != NULL)
			current = current->next;
		if (current->str != NULL)
		{
			new_hdc->command = (char **)malloc(sizeof(char *) * (i + 1));
			if (!new_hdc->command)
				return ;
			i = -1;
			while (current->str[++i])
				new_hdc->command[i] = ft_strdup(current->str[i]);
			new_hdc->command[i] = NULL;
		}
		if ((*token)->next->type == E_SPACE)
			(*token) = (*token)->next;
		new_hdc->break_word = ft_strdup((*token)->next->data);
		(*token) = (*token)->next;
	}
	new_heredoc(current, new_hdc);
}

void	add_heredoc(t_lexer **token, t_cmd *current)
{
	t_heredoc	*new_hdc;

	new_hdc = malloc(sizeof(t_heredoc));
	if (!new_hdc)
		exit(EXIT_FAILURE);
	fill_heredoc(token, current, new_hdc);
}

void	init_replace_dollar(int *i, int *j, char **res)
{
	*i = 0;
	*j = 0;
	*res = ft_strdup("");
}
