/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:02:38 by crystal           #+#    #+#             */
/*   Updated: 2024/05/28 14:29:50 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_res(size_t i, char **array)
{
	while (i > 0)
	{
		i--;
		free(array[i]);
	}
	free(array);
}

static size_t	count_words(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else if (s[i] == c)
			i++;
	}
	return (count);
}

static size_t	len(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	**split(char const *s, char c, char **res, size_t count)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < count)
	{
		while (s[j] && s[j] == c)
			j++;
		res[i] = ft_substr(s, j, len(&s[j], c));
		if (!res[i])
		{
			free_res(i, res);
			return (NULL);
		}
		while (s[j] && s[j] != c)
			j++;
		i++;
	}
	res[i] = NULL;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	nb;

	if (!s)
		return (NULL);
	nb = count_words(s, c);
	array = (char **)malloc(sizeof(char *) * (nb + 1));
	if (!array)
		return (NULL);
	array = split(s, c, array, nb);
	return (array);
}

// int main(void)
// {
// 	char **str;
// 	int	i = 0;
// 	str = ft_split("  tripouille  42  ", ' ');
// 	while (str[i] != NULL)
// 	{
// 		printf("%s\n", str[i]);
// 		free(str[i]);
// 		i++;
// 	}
// 	free(str);
// 	return 0;
// }
