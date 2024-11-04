/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:13:54 by agiliber          #+#    #+#             */
/*   Updated: 2024/11/04 17:54:03 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_break_word(t_cmd *cmd_parsing, t_env **data)
{
	if (!cmd_parsing->hdc->command && cmd_parsing->next == NULL)
	{
		ft_remove(cmd_parsing->hdc->file_name);
		return (1);
	}
	else if ((!cmd_parsing->hdc->command && cmd_parsing->next != NULL))
	{
		ft_remove(cmd_parsing->hdc->file_name);
		cmd_parsing = cmd_parsing->next;
		cmd_parsing->hdc->trigger = 2;
		exec_multiple_cmd(&cmd_parsing, data);
	}
	else if (cmd_parsing->next != NULL && cmd_parsing->next->hdc_count != 0)
		return (cmd_parsing = cmd_parsing->next, 1);
	else
	{
		cmd_parsing->hdc->trigger = 2;
		exec_multiple_cmd(&cmd_parsing, data);
	}
	return (0);
}

int	ft_remove(const char *pathname)
{
	struct stat	path_stat;

	if (lstat(pathname, &path_stat) == -1)
		return (-1);
	else
	{
		if (unlink(pathname) == -1)
			return (-1);
	}
	return (0);
}
