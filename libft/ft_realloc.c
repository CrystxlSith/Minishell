/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:14:34 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/09/23 10:56:36 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    *ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
    void	*new_ptr;

    if (new_size == 0)
    {
        free(ptr);
        return (NULL);
    }
    new_ptr = malloc(new_size);
    if (!new_ptr)
    {
        free(ptr);
        return (NULL);
    }
    if (ptr)
    {
        ft_memcpy(new_ptr, ptr, old_size);
        // free(ptr);
    }
    return (new_ptr);
}