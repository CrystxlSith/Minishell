/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 22:29:06 by crystal           #+#    #+#             */
/*   Updated: 2024/07/22 07:44:27 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i1;
	int		i2;
	int		i;
	int		j;

	i = -1;
	j = 0;
	i1 = ft_strlen(s1);
	i2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (i1 + i2) + 1);
	if (!str)
		return (NULL);
	while (s1[++i])
		str[j++] = s1[i];
	i = -1;
	while (s2[++i])
		str[j++] = s2[i];
	str[j] = '\0';
	return (str);
}
