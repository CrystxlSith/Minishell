/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:05:35 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/18 10:58:29 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	g_sig_status;

int	main(int ac, char **av, char **envp)
{
	t_minishell	minishell;
	t_cmd		*cmd_parsing;
	t_lexer		*tokens;
	t_env		*data;

	data = NULL;
	initiate_struc_envp(&data, envp);
	tokens = NULL;
	(void)ac;
	(void)av;
	if (generate_minishell_prompt(data, tokens, cmd_parsing, minishell) == -1)
		return (-1);
	return (0);
}
