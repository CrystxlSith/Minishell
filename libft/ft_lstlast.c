/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:56:42 by crystal           #+#    #+#             */
/*   Updated: 2024/05/14 11:39:45 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

// int main(void)
// {
//     t_list *element1 = ft_lstnew("manger");
//     t_list *element2 = ft_lstnew("du");
//     t_list *element3 = ft_lstnew("caca");

//     element1->next = element2;
//     element2->next = element3;
//     element3->next = NULL;  
//     t_list *last_element = ft_lstlast(element1);
//     printf("%s", (char *)last_element->content);
//     free(element1);
//     free(element2);
//     free(element3);

//     return 0;
// }