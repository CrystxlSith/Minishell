/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:04:40 by agiliber          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/10/10 14:47:17 by agiliber         ###   ########.fr       */
=======
/*   Updated: 2024/10/09 22:52:19 by crycry           ###   ########.fr       */
>>>>>>> 2c36ead87890904e4a65ff381dc03e4ceff4dbe4
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	heredoc(int index, t_minishell *mini, t_cmd **parsing, t_env **data)
{
	int	fd;

<<<<<<< HEAD
	if ((*parsing)->hdc->hdc_nb > 1)
=======
void	fill_input_hdc(t_lexer **tokens, t_cmd **parsing, t_env **data)
{
	t_lexer	*tmp;
	char	*res;
	int		fd;
	int		len;

	res = NULL;
	len = ft_strlen((*parsing)->hdc->break_word);
	tmp = *tokens;
	fd = open("/tmp/heredoc.txt", O_CREAT | O_RDWR | O_APPEND, 0777);
	if (fd == -1)
>>>>>>> 2c36ead87890904e4a65ff381dc03e4ceff4dbe4
	{
		if (check_break_word(*parsing, mini, index - (*parsing)->hdc->hdc_nb))
			(*parsing)->hdc->hdc_nb--;
		fd = open_heredoc_file(O_CREAT | O_RDWR | O_TRUNC);
		write_to_heredoc(fd, mini->line_read);
		close(fd);
	}
	else
	{
		fd = open_heredoc_file(O_CREAT | O_RDWR | O_APPEND);
		if (check_break_word(*parsing, mini, index - (*parsing)->hdc->hdc_nb))
		{
			(*parsing)->hdc->input_nbr = fd;
			(*parsing)->redir_nb--;
			exec_multiple_cmd(parsing, data);
			exit(EXIT_SUCCESS);
		}
		write_to_heredoc(fd, mini->line_read);
		(*parsing)->hdc->input_nbr = fd;
		close(fd);
	}
<<<<<<< HEAD
=======
	replace_dollar(&tmp->data, res, 0, 0);
	ft_putstr_fd(tmp->data, fd);
	ft_putstr_fd("\n", fd);
	(*parsing)->hdc->input_nbr = fd;
>>>>>>> 2c36ead87890904e4a65ff381dc03e4ceff4dbe4
}
