/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:36:35 by crystal           #+#    #+#             */
/*   Updated: 2024/05/14 11:39:31 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	if (!alst || !new)
		return ;
	new->next = *alst;
	*alst = new;
}

// int main(void)
// {
// 	t_list *lst = NULL;
// t_list *new = ft_lstnew("Hello");
// ft_lstadd_front(&lst, new);

// t_list *lst = ft_lstnew("Hello");
// t_list *new = ft_lstnew("World");
// ft_lstadd_front(&lst, new);
// t_list *current = new;
// printf("%s", (char *)current->content);
// 	return 0;
// }