/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:33:26 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/09/02 16:20:43 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "includes/token.h"

int main(int argc, char const *argv[], char const *env[])
{
	t_minishell	minishell;

	if (argc || argv || env)
		ft_memset(&minishell ,0 , sizeof(t_minishell));
	
	while (1)
	{
		// Retourne la ligne entree dans le terminal et ecris un prompt voulu
		minishell.line_read = readline("minishell > ");
		if (minishell.line_read)
		{
			// Permet l'utilisation des fleches pour naviguer dans
			// l'historique des commandes effectuees
			add_history(minishell.line_read);
		} 
		// Simule une sortie qui inclut un saut de ligne
		printf("Exécution d'une commande...\n");
		// Tokenize la commande
		tokenize(minishell.line_read);
		// Indique à readline que nous sommes sur une nouvelle ligne
		rl_on_new_line();
		// rl_redisplay();  // Rafraîchit l'affichage du prompt
		free(minishell.line_read);
	}
	return 0;
}
