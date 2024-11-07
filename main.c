/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:05:35 by agiliber          #+#    #+#             */
/*   Updated: 2024/11/07 16:11:09 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	g_sig_status = 0;

int	initiate_env_supp(t_env **data)
{
	*data = malloc(sizeof(t_env));
	if (!data)
		return (-1);
	(*data)->var = NULL;
	(*data)->pwd = NULL;
	(*data)->old_pwd = NULL;
	(*data)->exit_code = 0;
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	int			stored_status;
	t_cmd		*cmd_parsing;
	t_lexer		*tokens;
	t_env		*data;

	data = NULL;
	if (*envp)
		initiate_struc_envp(&data, envp);
	else
		initiate_env_supp(&data);
	tokens = NULL;
	cmd_parsing = NULL;
	(void)ac;
	(void)av;
	remove_hdc_file();
	if (generate_minishell_prompt(data, tokens, cmd_parsing) == -1)
	{
		stored_status = data->exit_code;
		return (free_minishell(data), exit(stored_status), 1);
	}
	free_minishell(data);
	return (0);
}
