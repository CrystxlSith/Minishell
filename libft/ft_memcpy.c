/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 00:44:55 by wbelyne           #+#    #+#             */
/*   Updated: 2024/10/25 14:39:19 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*d;
	size_t			i;

	d = (unsigned char *)dst;
	i = 0;
	if (!dst || !src)
		return (NULL);
	while (i < n)
	{
		*d = *(unsigned char *)src;
		d++;
		src++;
		i++;
	}
	return (dst);
}
