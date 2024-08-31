/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 19:52:22 by crystal           #+#    #+#             */
/*   Updated: 2024/05/23 10:42:49 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*La fonction memchr() examine les n premiers 
octets de la zone mémoire pointée par s à la recherche du caractère c.
Le premier octet correspondant à c (
interprété comme un unsigned char) arrête l'opération.*/

void	*ft_memchr(const void *s, int c, size_t n)
{
	if (c > 255)
		c = c % 256;
	while (n)
	{
		if (*(unsigned char *)s == (unsigned char)c)
			return ((void *)s);
		s++;
		n--;
	}
	return (NULL);
}
