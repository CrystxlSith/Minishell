/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:40:57 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/06/07 11:52:57 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	sizeintt(long int n)
{
	int	i;

	i = 0;
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_uitoa(unsigned long int n)
{
	int					size;
	char				*result;
	unsigned long int	nb;

	nb = n;
	size = sizeintt(nb);
	if (nb == 0)
		return (ft_strdup("0"));
	result = (char *)malloc(sizeof(char) * (size + 1));
	if (!result)
		return (NULL);
	result[size] = '\0';
	while (nb)
	{
		result[--size] = (nb % 10) + 48;
		nb /= 10;
	}
	return (result);
}
