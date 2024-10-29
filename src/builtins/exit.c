/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:37:11 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/29 12:37:34 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_array_dup(char **array)
{
	char	**new_array;
	int		i;

	if (!array)
		return (NULL);
	i = 0;
	while (array[i])
		i++;
	new_array = malloc((i + 1) * sizeof(char *));
	if (!new_array)
		return (NULL);
	i = 0;
	while (array[i])
	{
		new_array[i] = strdup(array[i]);
		i++;
	}
	new_array[i] = NULL;
	return (new_array);
}

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	exit_code(char **str)
{
	int		code;

	if (!str || !str[1])
		code = 0;
	else
		code = ft_atoi(str[1]);
	ft_free_array(str);
	exit(code);
}

int	ft_exit_shell(t_cmd *cmd_parsing, t_env *data, t_lexer *tokens)
{
	char	**str;

	if (cmd_parsing->str[1] && !is_numeric(cmd_parsing->str[1]))
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd("minishell : exit ", STDERR_FILENO);
		ft_putstr_fd(cmd_parsing->str[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		free_all_line(tokens, cmd_parsing);
		free_minishell(data);
		//free(data);
		exit(255);
	}
	if (cmd_parsing->str[1] && cmd_parsing->str[2])
	{
		ft_putstr_fd(EXIT_ARGS_ERR, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	str = ft_array_dup(cmd_parsing->str);
	free_all_line(tokens, cmd_parsing);
	free_minishell(data);
	//free(data);
	exit_code(str);
	return (EXIT_SUCCESS);
}
