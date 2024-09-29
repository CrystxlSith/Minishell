/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycry <crycry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:57:35 by crycry            #+#    #+#             */
/*   Updated: 2024/09/28 14:52:39 by crycry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_error(char *error, char *token)
{
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    ft_putstr_fd(error, STDERR_FILENO);
    ft_putstr_fd("`", STDERR_FILENO);
    ft_putstr_fd(token, STDERR_FILENO);
    ft_putstr_fd("'", STDERR_FILENO);
    ft_putstr_fd("\n", STDERR_FILENO);
    minishell.last_exit_status = 258;
    printf("minishell last exit status: %d\n", minishell.last_exit_status);

}