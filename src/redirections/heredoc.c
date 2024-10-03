/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:04:40 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/03 13:17:21 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	initiate_hdc_struc(t_cmd *parsing)
{
	parsing->hdc = malloc(sizeof(t_heredoc));
	if (!parsing->hdc)
		return (-1);
	parsing->hdc->break_word = NULL;
	parsing->hdc->command = NULL;
	parsing->hdc->input_hdc = NULL;
	parsing->hdc->input_nbr = 0;
	parsing->hdc->single_input = NULL;
	return (0);
}

char	**ft_realloc_hdc(int new_size, t_cmd **parsing)
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
		size = ft_strlen((*parsing)->hdc->input_hdc[i]);
		new_tab[i] = (char *)malloc(size + 1);
		if (!new_tab[i])
			return (free_rest_tab(new_tab, i - 1), NULL);
		ft_memcpy(new_tab[i], (*parsing)->hdc->input_hdc[i], size + 1);
		i++;
	}
	new_tab[old_size] = NULL;
	return (new_tab);
}

void	duplicate_hdc(t_cmd **parsing)
{
	int	i;

	i = 0;
	while ((*parsing)->hdc->input_hdc[i])
		i++;
	if ((*parsing)->hdc->single_input != NULL)
	{
		(*parsing)->hdc->input_hdc[i] = \
			ft_strdup((*parsing)->hdc->single_input);
		(*parsing)->hdc->input_hdc[i + 1] = NULL;
		(*parsing)->hdc->input_nbr++;
		free((*parsing)->hdc->single_input);
	}
}

void	fill_heredoc(t_cmd **parsing, int size)
{
	char	**new_tab;

	new_tab = ft_realloc_hdc(size, parsing);
	if (!new_tab)
	{
		free((*parsing)->hdc->single_input);
		return ;
	}
	duplicate_hdc(parsing);
	free_all(new_tab);
}

void	heredoc(t_cmd **parsing, t_env **data)
{
	int		len;
	int		i;

	i = 0;
	if (initiate_hdc_struc(*parsing) == -1)
	{
		perror("struct heredoc");
		exit(EXIT_FAILURE);
	}

	len = ft_strlen((*parsing)->hdc->break_word);
	while (ft_strncmp((*parsing)->hdc->break_word, \
		(*parsing)->hdc->input_hdc[i], len) != 0)
	{
		fill_heredoc(parsing, i);
		i++;
	}
	exec_cmd_minishell(parsing, data);
}
