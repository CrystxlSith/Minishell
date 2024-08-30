/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:33:26 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/08/30 11:41:07 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int main(/*int argc, char const *argv[], char const *env[]*/)
{
    char *input;
    char *exitt = "minishell> exit";

    while ((input = readline("jopfeiff@made-f0Br8s11:~$ ")) != NULL) {
        if (*input) {
            add_history(input);
        }
        
        // Simule une sortie qui inclut un saut de ligne
        printf("Exécution d'une commande...\n");
        
        // Indique à readline que nous sommes sur une nouvelle ligne
        rl_on_new_line();
        // rl_redisplay();  // Rafraîchit l'affichage du prompt
        if (input == exitt)
            return (free(input), exit(1), 0);
        free(input);
    }
    return 0;
}
