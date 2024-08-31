/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 21:31:37 by crystal           #+#    #+#             */
/*   Updated: 2024/05/23 11:38:40 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*strnstr - Find the first substring in a length-limited string*/

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	if (big == little || *little == '\0')
		return ((char *)big);
	while (big[i] && len)
	{
		j = 0;
		if (big[i] == little[j])
		{
			k = len + 1;
			while (little[j] && big[i + j] == little[j] && --k)
				j++;
		}
		if (len == 0)
			return (NULL);
		if (little[j] == '\0')
			return ((char *)big + i);
		i++;
		len--;
	}
	return (NULL);
}
// int main(int argc, char const *argv[])
// {
// 	char *str;
// 	if (argc == 3)
// 	{
// 		str = ft_strnstr(argv[1], argv[2], 8);
// 	}
// 	printf("%s", str);
// 	return 0;
// }
