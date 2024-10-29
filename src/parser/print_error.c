/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:57:35 by crycry            #+#    #+#             */
/*   Updated: 2024/10/29 15:02:15 by agiliber         ###   ########.fr       */
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
	g_sig_status = 258;
}

void	print_hdc_error(int i , char *token2)
{
	char	*token;
	token = ft_itoa(i);
	ft_putstr_fd("minishell: warning: here-document at line ", STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putstr_fd(" delimited by end-of-file (wanted ", STDERR_FILENO);
	ft_putstr_fd("`", STDERR_FILENO);
	ft_putstr_fd(token2, STDERR_FILENO);
	ft_putstr_fd("'", STDERR_FILENO);
	ft_putstr_fd(")", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	free(token);
	g_sig_status = 258;
}
