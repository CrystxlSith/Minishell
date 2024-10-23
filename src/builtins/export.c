/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:27:49 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/23 15:31:59 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Fonction principale appelee dans la fonction Builtins. Recupere le flag
// donne en input. Duplique la commande a inserer/modifier dans le tableau
// d'environnement
void	export(char *input, t_env **data)
{
	char	*cmd;
	char	*flag;
	int		i;

	i = 0;
	while (input[i] && input[i] != '=')
		i++;
	if (input[i] == '\0' || i == 0)
		return ;
	flag = malloc(sizeof(char) * (i + 1));
	if (!flag)
		return ;
	flag = ft_strncpy(flag, input, i);
	cmd = input;
	update_env_tab_export(flag, cmd, data);
	free(flag);
}
