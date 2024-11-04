/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_hdc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:04:40 by agiliber          #+#    #+#             */
/*   Updated: 2024/11/04 16:36:27 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_heredoc(t_cmd **cmd_parsing, t_env **data)
{
	t_cmd	*tmp;
	int		nbr;

	nbr = detect_hdc(cmd_parsing);
	generate_hdc_files(cmd_parsing, nbr);
	tmp = *cmd_parsing;
	while (nbr > 0 && tmp)
	{
		handle_heredoc_input(tmp, data);
		close(tmp->hdc->hdc_fd);
		tmp = tmp->next;
		nbr--;
	}
	return (0);
}

void	hdc_force_exit(int i, t_cmd *cmd_parsing)
{
	print_hdc_error(i, cmd_parsing->hdc->break_word);
	close(cmd_parsing->hdc->hdc_fd);
	exit(EXIT_SUCCESS);
}

void	handle_heredoc_child(t_cmd *cmd_parsing, t_env **data, char *res)
{
	t_minishell	mini;
	static int	i;

	i = 0;
	while (1)
	{
		init_signals(1);
		mini.line_read = readline("> ");
		replace_dollar_hdc(&mini.line_read, res, data);
		i++;
		if (need_to_continue(mini, cmd_parsing, data) == 1)
			continue ;
		else if (check_break_word(cmd_parsing, &mini, \
		cmd_parsing->hdc->hdc_fd, data) > 1)
			break ;
		write_to_heredoc(cmd_parsing->hdc->hdc_fd, mini.line_read);
		free(mini.line_read);
	}
	if (!mini.line_read)
		hdc_force_exit(i, cmd_parsing);
}

int	need_to_continue(t_minishell mini, t_cmd *cmd_parsing, t_env **data)
{
	if (mini.line_read && mini.line_read[0] == '\0')
	{
		write_to_heredoc(cmd_parsing->hdc->hdc_fd, mini.line_read);
		free(mini.line_read);
		return (1);
	}
	if (check_break_word(cmd_parsing, &mini, \
	cmd_parsing->hdc->hdc_fd, data) == 1)
	{
		free(mini.line_read);
		return (1);
	}
	return (0);
}

void	replace_dollar_hdc(char **input, char *res, t_env **data)
{
	t_replace_params	params;

	if (*input)
	{
		params.input = input;
		params.res = res;
		params.data = data;
		init_replace_dollar(&params.i, &params.j, &params.res);
		while ((*params.input)[params.j])
		{
			if ((*params.input)[params.j] == '$')
			{
				process_dollar(&params);
			}
			else
			{
				params.res = build_res(params.res, params.i, \
				params.j, params.input);
				free_increment(&params.i, &params.j);
			}
		}
		free(*params.input);
		*params.input = params.res;
	}
}
