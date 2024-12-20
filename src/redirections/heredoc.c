/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:04:40 by agiliber          #+#    #+#             */
/*   Updated: 2024/11/07 17:46:07 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	detect_hdc(t_cmd **cmd_parsing)
{
	t_cmd	*tmp;
	int		count;

	count = 0;
	tmp = *cmd_parsing;
	while (tmp)
	{
		if (tmp->hdc_count != 0)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

int	open_hdc_file(char *file_name)
{
	int		fd;

	fd = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0777);
	return (fd);
}

void	generate_hdc_files(t_cmd **cmd_parsing, int count)
{
	t_cmd	*tmp;
	char	*file_name;
	int		i;
	char	*index;

	i = 1;
	tmp = *cmd_parsing;
	while (tmp && i <= count)
	{
		if (tmp->hdc_count != 0)
		{
			index = ft_itoa(i);
			file_name = ft_strdup("/tmp/heredoc");
			file_name = ft_strjoin(file_name, index);
			file_name = ft_strjoin(file_name, ".txt");
			tmp->hdc->hdc_fd = open_hdc_file(file_name);
			if (tmp->hdc->hdc_fd == -1)
				return ;
			tmp->hdc->file_name = ft_strdup(file_name);
			i++;
			free(file_name);
			free(index);
		}
		tmp = tmp->next;
	}
}

int	check_break_word(t_cmd *cmd_parsing, t_minishell *mini, \
int fd, t_env **data)
{
	int	len;

	len = ft_strlen(cmd_parsing->hdc->break_word);
	if (mini->line_read == NULL || ft_strncmp(cmd_parsing->hdc->break_word, \
	mini->line_read, len + 1) == 0)
	{
		if (cmd_parsing->hdc->next != NULL)
		{
			ft_remove(cmd_parsing->hdc->file_name);
			parse_open(cmd_parsing);
			if (cmd_parsing->hdc->hdc_fd == -1)
				return (-1);
			cmd_parsing->hdc->file_name = \
				ft_strdup(cmd_parsing->hdc->prev->file_name);
			return (close(fd), 1);
		}
		else
		{
			if (!mini->line_read)
				hdc_force_exit(mini->i, cmd_parsing);
			handle_break_word(cmd_parsing, data);
			return (exit((*data)->exit_code), close(fd), 2);
		}
	}
	return (0);
}

int	handle_heredoc_input(t_cmd *cmd_parsing, t_env **data)
{
	int		pid;
	int		status;
	char	*res;

	res = NULL;
	status = 0;
	pid = fork();
	(*data)->heredoc = 0;
	if (pid == -1)
		return (-1);
	if (pid == 0)
		handle_heredoc_child(cmd_parsing, data, res);
	(*data)->heredoc = 1;
	waitpid(pid, &status, 0);
	(*data)->exit_code = exit_status(status, data);
	return (0);
}
