/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:27:49 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/02 11:56:47 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Fonction principale appelee dans la fonction Builtins. Recupere le flag
// donne en input. Duplique la commande a inserer/modifier dans le tableau
// d'environnement
void	export(char *input, t_env **data)
{
	char	*cmd;
	char	*flag;
	int		i;

	i = 0;
	printf("input export : %s\n", input);
	while (input[i] != '=')
		i++;
	flag = malloc(sizeof(char) * (i + 1));
	if (!flag)
		return ;
	flag = ft_strncpy(flag, input, i);
	printf("flag export : %s\n", flag);
	cmd = ft_strdup(input);
	printf("cmd export : %s\n", cmd);
	if (!cmd)
		return ;
	update_env_tab_export(flag, cmd, data);
	free(flag);
}
