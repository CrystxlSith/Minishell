/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycry <crycry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:50:52 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/10/30 19:36:34 by crycry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	add_count_elem(char **data)
{
	int	i;

	i = 0;
	while (data[i])
		i++;
	return (i);
}

void	init_cmd(t_cmd **head, t_cmd **current)
{
	*head = malloc(sizeof(t_cmd));
	*current = *head;
	(*head)->index = 0;
	(*head)->elem_nb = 0;
	(*head)->str = NULL;
	(*head)->redir_nb = 0;
	(*head)->here_doc = NULL;
	(*head)->hdc_count = 0;
	(*head)->hdc = NULL;
	(*head)->redir = NULL;
	(*head)->next = NULL;
	(*head)->prev = NULL;
	(*head)->index = 1;
}

t_cmd	*create_new_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->str = NULL;
	new_cmd->redir_nb = 0;
	new_cmd->elem_nb = 0;
	new_cmd->here_doc = NULL;
	new_cmd->hdc_count = 0;
	new_cmd->hdc = NULL;
	new_cmd->redir = NULL;
	new_cmd->next = NULL;
	new_cmd->prev = NULL;
	return (new_cmd);
}

int	handle_question(char **res, int *i, char **input, int *j)
{
	char	*tmp2;

	printf("sig status = %d", g_sig_status);
	tmp2 = ft_itoa(g_sig_status);
	printf("sig status = %s \n", tmp2);
	if (!tmp2)
		return (0);
	if ((*input)[*j] && (*input)[*j + 1])
	{
		if ((*input)[*j] == '$' && (*input)[*j + 1] == '?')
		{
			char *new_res = ft_strjoin(*res, tmp2);
			if (!new_res)
			{
				free(tmp2);
				return (0);
			}
			*res = new_res;
			*i += ft_strlen(tmp2);
			*j += 2;
			free(tmp2);
			return (1);
		}
	}
	free(tmp2);
	return (0);
}
