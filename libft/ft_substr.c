/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 20:31:43 by crystal           #+#    #+#             */
/*   Updated: 2024/05/20 13:00:06 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	j;

	if (!s)
		return (NULL);
	if (len > (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	if (start > ft_strlen(s))
		len = 0;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	j = 0;
	if (start < ft_strlen(s))
	{
		while (s[start] && len--)
		{
			str[j] = s[start];
			start++;
			j++;
		}
	}
	str[j] = '\0';
	return (str);
}
// int main(void)
// {
// 	char *s = ft_substr(, 42, 42000000);
// 	printf("%s", s);
// 	return 0;
// }
