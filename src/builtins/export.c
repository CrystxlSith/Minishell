/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycry <crycry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:27:49 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/31 03:24:35 by crycry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_input_export(char *input, t_env **data)
{
	int	i;

	i = 0;
	if (!input)
	{
		while ((*data)->var[i])
		{
			printf("%s", "export ");
			printf("%s\n", (*data)->var[i]);
			i++;
		}
		return (-1);
	}
	if ((input[0] == '=' && input[1] == '\0')
		|| (input[0] < 65) || (input[0] > 90
			&& input[0] < 97) || input[0] > 122)
		return (-1);
	while (input[i] && input[i] != '=')
		i++;
	if (input[i] == '\0')
		return (-1);
	return (i);
}

// Fonction principale appelee dans la fonction Builtins. Recupere le flag
// donne en input. Duplique la commande a inserer/modifier dans le tableau
// d'environnement
int	export(char *input, t_env **data)
{
	char	*cmd;
	char	*flag;
	int		i;

	i = check_input_export(input, data);
	if (i == -1 || i == 0)
	{
		perror("export");
		return (1);
	}
	flag = malloc(sizeof(char) * (i + 1));
	if (!flag)
		return (1);
	flag = ft_strncpy(flag, input, i);
	cmd = input;
	update_env_tab_export(flag, cmd, data);
	return (0);
	free(flag);
}
