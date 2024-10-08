/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:04:40 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/08 11:38:34 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	initiate_hdc_struc(t_cmd **parsing)
{
	(*parsing)->hdc = malloc(sizeof(t_heredoc));
	if (!(*parsing)->hdc)
		return (-1);
	(*parsing)->hdc->break_word = NULL;
	(*parsing)->hdc->command = NULL;
	(*parsing)->hdc->input_hdc = NULL;
	(*parsing)->hdc->input_nbr = 0;
	(*parsing)->hdc->single_input = NULL;
	return (0);
}

void	fill_input_hdc(t_lexer **tokens, t_cmd **parsing, t_env **data)
{
	t_lexer	*tmp;
	int		fd;
	int		len;

	len = ft_strlen((*parsing)->hdc->break_word);
	tmp = *tokens;
	fd = open("/tmp/heredoc.txt", O_CREAT | O_RDWR | O_APPEND, 0777);
	if (fd == -1)
	{
		perror("open fd heredoc");
		exit(EXIT_FAILURE);
	}
	if (ft_strncmp((*parsing)->hdc->break_word, tmp->data, len) == 0)
	{
		(*parsing)->hdc->input_nbr = fd;
		(*parsing)->redir_nb--;
		exec_multiple_cmd(parsing, data);
		exit(0);
	}
	ft_putstr_fd(tmp->data, fd);
	ft_putstr_fd("\n", fd);
	(*parsing)->hdc->input_nbr = fd;
}
