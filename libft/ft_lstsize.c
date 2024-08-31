/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:41:45 by crystal           #+#    #+#             */
/*   Updated: 2024/05/14 11:40:01 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

// int main() {
//     t_list *element1 = (t_list *)malloc(sizeof(t_list));
//     t_list *element2 = (t_list *)malloc(sizeof(t_list));
//     t_list *element3 = (t_list *)malloc(sizeof(t_list));

//     element1->next = element2;
//     element2->next = element3;
//     element3->next = NULL;  
//     int size = ft_lstsize(element1);
//     printf("Taille de la liste : %d\n", size);
//     free(element1);
//     free(element2);
//     free(element3);

//     return 0;
// }