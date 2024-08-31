/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:26:05 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/07/22 07:43:42 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_gnl(char *s1, char const *s2)
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
	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (i1 + i2 + 1));
	if (!str)
		return (NULL);
	while (s1[++i])
		str[j++] = s1[i];
	i = -1;
	while (s2[++i])
		str[j++] = s2[i];
	str[j] = '\0';
	free(s1);
	return (str);
}
