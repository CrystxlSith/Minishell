/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:59:47 by crystal           #+#    #+#             */
/*   Updated: 2024/05/28 14:20:58 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Itère sur la liste ’lst’ et applique la fonction
’f ’au contenu de chaque élément. Crée une nouvelle
liste résultant des applications successives de
’f’. La fonction ’del’ est là pour détruire le
contenu d’un élément si nécessaire.*/

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*save;

	if (!lst || !f || !del)
		return (0);
	new_list = ft_lstnew(f(lst->content));
	if (!new_list)
		return (0);
	lst = lst->next;
	save = new_list;
	while (lst)
	{
		new_list->next = ft_lstnew(f(lst->content));
		if (!new_list->next)
		{
			ft_lstclear(&save, del);
			return (save);
		}
		new_list = new_list->next;
		lst = lst->next;
	}
	new_list->next = NULL;
	return (save);
}

// void *duplicate_content(void *content) {
//     int *new_content = malloc(sizeof(int));
//     if (new_content) {
//         *new_content = (*(int *)content) * 2;
//     }
//     return new_content;
// }

// t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
// {
// 	t_list	*new_list;
// 	t_list	*new_node;
// 	void	*set;

// 	if (!lst || !f || !del)
// 		return (NULL);
// 	new_list = NULL;
// 	while (lst)
// 	{
// 		set = f(lst->content);
// 		new_node = ft_lstnew(set);
// 		if (!new_node)
// 		{
// 			del(set);
// 			ft_lstclear(&new_list, (*del));
// 			return (new_list);
// 		}
// 		ft_lstadd_back(&new_list, new_node);
// 		lst = lst->next;
// 	}
// 	return (new_list);
// }
// void delete_content(void *content) {
//     free(content);
// }

// int main() {
//     t_list *lst = ft_lstnew(malloc(sizeof(int)));
//     t_list *elem2 = ft_lstnew(malloc(sizeof(int)));
//     t_list *elem3 = ft_lstnew(malloc(sizeof(int)));

//     *(int *)(lst->content) = 1;
//     *(int *)(elem2->content) = 2;
//     *(int *)(elem3->content) = 3;

//     lst->next = elem2;
//     elem2->next = elem3;

//     t_list *new_lst = ft_lstmap(lst, duplicate_content, delete_content);

//     // Print original list
//     t_list *temp = lst;
//     printf("Original list:\n");
//     while (temp) {
//         printf("%d -> ", *(int *)temp->content);
//         temp = temp->next;
//     }
//     printf("NULL\n");

//     // Print new list
//     temp = new_lst;
//     printf("New list:\n");
//     while (temp) {
//         printf("%d -> ", *(int *)temp->content);
//         temp = temp->next;
//     }
//     printf("NULL\n");

//     // Clean up
//     temp = lst;
//     while (temp) {
//         t_list *next = temp->next;
//         delete_content(temp->content);
//         free(temp);
//         temp = next;
//     }

//     temp = new_lst;
//     while (temp) {
//         t_list *next = temp->next;
//         delete_content(temp->content);
//         free(temp);
//         temp = next;
//     }

//     return 0;
// }