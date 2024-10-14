/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:46:47 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/14 11:57:42 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	initiate_hdc_struc(t_cmd **parsing)
{
	(*parsing)->hdc = malloc(sizeof(t_heredoc));
	if (!(*parsing)->hdc)
		return (-1);
	(*parsing)->hdc->break_word = NULL;
	(*parsing)->hdc->command = NULL;
	(*parsing)->hdc->hdc_count = 0;
	(*parsing)->hdc->next = NULL;
	return (0);
}

/* char	**ft_realloc_hdc(int new_size, t_cmd **parsing)
{
	int		old_size;
	char	**new_tab;
	int		i;
	int		size;

	if (new_size == 0)
		return (NULL);
	new_tab = (char **)malloc(sizeof(char *) * (new_size + 1));
	if (!new_tab)
		return (NULL);
	old_size = 0;
	if (new_size > 0)
		old_size = new_size -1;
	i = 0;
	while (i < old_size)
	{
		size = ft_strlen((*parsing)->hdc->break_word[i]);
		new_tab[i] = (char *)malloc(size + 1);
		if (!new_tab[i])
			return (free_rest_tab(new_tab, i - 1), NULL);
		ft_memcpy(new_tab[i], (*parsing)->hdc->break_word[i], size + 1);
		i++;
	}
	new_tab[old_size] = NULL;
	return (new_tab);
} */

int	open_heredoc_file(int flags)
{
	int	fd;

	fd = open("/tmp/heredoc.txt", flags, 0777);
	if (fd == -1)
	{
		perror("open fd heredoc");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	write_to_heredoc(int fd, char *line)
{
	ft_putstr_fd(line, fd);
	ft_putstr_fd("\n", fd);
}

int	check_break_word(t_cmd *parsing, t_minishell *minishell, int i)
{
	char	*break_word;
	char	*line;
	size_t	len;

	break_word = parsing->hdc->break_word;
	line = minishell->line_read;
	len = ft_strlen(break_word);
	if (ft_strncmp(break_word, line, len) == 0)
		return (1);
	return (0);
}
