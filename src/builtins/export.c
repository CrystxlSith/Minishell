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
		i = -1;
		while ((*data)->var[++i])
			printf("export %s\n", (*data)->var[i]);
		return (-1);
	}
	if (!ft_isalpha(input[0]) && input[0] != '_')
	{
		ft_printf_fd(2, "bash: export: `%s': not a valid identifier\n", input);
		return (-1);
	}
	i = 1;
	while (input[i] && input[i] != '=')
	{
		if (!ft_isalnum(input[i]) && input[i] != '_')
			return (-1);
		i++;
	}
	return (1);
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
		return (1);
	flag = malloc(sizeof(char) * (i + 1));
	if (!flag)
		return (1);
	flag = ft_strncpy(flag, input, i);
	cmd = input;
	update_env_tab_export(flag, cmd, data);
	free(flag);
	return (0);
}
