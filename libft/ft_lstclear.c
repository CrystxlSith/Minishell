/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:14:28 by wbelyne           #+#    #+#             */
/*   Updated: 2024/05/14 11:39:33 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*next;

	if (!del || !lst || !*lst)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		del(current->content);
		free(current);
		current = next;
	}
	*lst = NULL;
}

// void print_list(t_list *head) {
//     printf("Liste: ");
//     while (head != NULL) {
//         printf("%s ", (char *)head->content);
//         head = head->next;
//     }
//     printf("\n");
// }

// int main(void) 
// {
// 	char *content = (char *)malloc(sizeof(char) * 6);
// 	sprintf(content, "Hello");
// 	char *end = (char *)malloc(sizeof(char) * 6);
// 	sprintf(end, "world");
// 	t_list *lst = ft_lstnew(content);
// 	ft_lstadd_back(&lst, ft_lstnew(end));
// 	print_list(lst);
// 	ft_lstclear(&lst, &ft_delete);
// 	printf("vide\n");
// 		return 0;
// }