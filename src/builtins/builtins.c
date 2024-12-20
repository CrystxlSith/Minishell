/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycry <crycry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:19:17 by agiliber          #+#    #+#             */
/*   Updated: 2024/11/06 19:23:09 by crycry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtins(t_cmd **parsing, t_env **data)
{
	int	i;
	int	status;

	if (!(*parsing)->str)
		return (-1);
	i = 0;
	if (ft_strncmp((*parsing)->str[i], "echo", 5) == 0)
		status = echo((*parsing)->str, data);
	else if (ft_strncmp((*parsing)->str[i], "unset", 6) == 0)
		status = unset((*parsing)->str[++i], data);
	else if (ft_strncmp((*parsing)->str[i], "env", 4) == 0)
		status = env(data);
	else if (ft_strncmp((*parsing)->str[i], "pwd", 4) == 0)
		status = pwd(parsing, data);
	else if (ft_strncmp((*parsing)->str[i], "export", 7) == 0)
		status = export((*parsing)->str[++i], data);
	else if (ft_strncmp((*parsing)->str[i], "cd", 3) == 0)
		status = cd((*parsing)->str[++i], data);
	else
		return (1);
	(*data)->exit_code = status;
	return (status);
}
