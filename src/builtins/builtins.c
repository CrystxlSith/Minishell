/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:19:17 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/18 14:41:55 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtins(t_cmd **parsing, t_env **data)
{
	int	i;

	if (!(*parsing)->str)
		return (free_all((*data)->var), free_all((*parsing)->str), 0);
	i = 0;
	if (ft_strncmp((*parsing)->str[i], "echo", 5) == 0)
		echo((*parsing)->str, data);
	else if (ft_strncmp((*parsing)->str[i], "pwd", 4) == 0)
		pwd(data);
	else if (ft_strncmp((*parsing)->str[i], "env", 4) == 0)
		env(data);
	else if (ft_strncmp((*parsing)->str[i], "export", 7) == 0)
		export((*parsing)->str[++i], data);
	else if (ft_strncmp((*parsing)->str[i], "cd", 3) == 0)
		cd((*parsing)->str[++i], data);
	else if (ft_strncmp((*parsing)->str[i], "unset", 6) == 0)
		unset((*parsing)->str[++i], data);
	else
		return (free_all((*parsing)->str), 0);
	return (0);
}
