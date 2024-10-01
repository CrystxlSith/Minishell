/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariannedubuard <mariannedubuard@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:58:22 by crystal           #+#    #+#             */
/*   Updated: 2024/09/26 16:50:13 by mariannedub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb && size && nmemb > (UINT_MAX / size))
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	if (size >= 18446744073709551615UL || nmemb >= 18446744073709551615UL)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
// int main(void)
// {
// 	void	*ptr;
// 	ptr = ft_calloc(0,0);
// 	free(ptr);
// 	ptr = ft_calloc(0,5);
// 	free(ptr);
// 	return 0;
// }
