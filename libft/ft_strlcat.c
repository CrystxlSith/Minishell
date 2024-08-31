/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:30:23 by crystal           #+#    #+#             */
/*   Updated: 2024/05/23 10:37:15 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <bsd/string.h>

// strlcat - Append a length-limited, NUL-terminated string to another 

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dlen;
	size_t	slen;
	size_t	i;

	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	i = 0;
	if (size == 0)
		return (slen);
	if (size < dlen)
		return (slen + size);
	while (src[i] && (dlen + i) < (size - 1))
	{
		dst[dlen + i] = src[i];
		i++;
	}
	if ((dlen + i) < size)
		dst[dlen + i] = '\0';
	return (dlen + slen);
}

// int main() 
// {
//     char dst[20] = "Hello, ";
//     char src[] = "world!";
//     size_t dst_len = strlen(dst);
//     size_t result = ft_strlcat(dst, src, 0);
//     printf("Chaîne concaténée : %s\n", dst);
//     printf("Longueur totale : %zu\n", result);
//     printf("Longueur initiale de dst : %zu\n", dst_len);
//     printf("Taille de dst après concaténation : %zu\n", strlen(dst));
//     return 0;
// }