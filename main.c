/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:05:35 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/29 12:48:04 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
echo seul segfuault
fausse commande devrait ecrire bash: <commande>:command not found
*/

int	g_sig_status;

int	main(int ac, char **av, char **envp)
{
	t_cmd		*cmd_parsing;
	t_lexer		*tokens;
	t_env		*data;

	data = NULL;
	initiate_struc_envp(&data, envp);
	tokens = NULL;
	cmd_parsing = NULL;
	(void)ac;
	(void)av;
	remove_hdc_file();
	if (generate_minishell_prompt(data, tokens, cmd_parsing) == -1)
		return (free_minishell(data), -1);
	free_minishell(data);
	return (0);
}

/*d*/
