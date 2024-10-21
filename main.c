/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:05:35 by agiliber          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/10/18 11:24:38 by agiliber         ###   ########.fr       */
=======
/*   Updated: 2024/10/21 14:18:41 by agiliber         ###   ########.fr       */
>>>>>>> Minishell_AGT
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
	if (generate_minishell_prompt(data, tokens, cmd_parsing) == -1)
		return (-1);
<<<<<<< HEAD
=======
	free_all(data->var);
	free(data);
>>>>>>> Minishell_AGT
	return (0);
}
