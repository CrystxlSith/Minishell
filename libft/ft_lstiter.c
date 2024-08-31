/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 21:00:00 by crystal           #+#    #+#             */
/*   Updated: 2024/05/14 11:39:40 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <ctype.h>

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

// int main(void)
// {
// 	char *mall = (char *)malloc(sizeof(char) * 6);
// 	sprintf(mall, "hello");
// 	t_list *head = ft_lstnew(mall);
// 	ft_lstadd_back(&head, ft_lstnew("world"));
// 	ft_lstiter(head, &ft_alph);
// 	return 0;
// }