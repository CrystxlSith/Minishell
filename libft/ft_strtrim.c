/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crystal <crystal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:52:52 by crystal           #+#    #+#             */
/*   Updated: 2024/05/25 15:37:46 by crystal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "unistd.h"

static int	ft_is_in_set(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*newstr;
	int		start;
	int		end;

	start = 0;
	end = ft_strlen(s1);
	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	while (s1[start] && ft_is_in_set(s1[start], set))
		start++;
	while (end > start && ft_is_in_set(s1[end - 1], set))
		end--;
	newstr = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!newstr)
		return (NULL);
	ft_strncpy(newstr, &s1[start], (end - start));
	newstr[end - start] = '\0';
	return (newstr);
}

// int main(void)
// {
// 	char *str;
// 	// str = ft_strtrim("   xxxtripouille", " x");
// 	str = ft_strtrim("tripouille   xxx", " x");
// 	printf("%s", str);
// 	return 0;
// }
