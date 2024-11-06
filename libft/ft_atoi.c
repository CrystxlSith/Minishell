/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 19:23:10 by crystal           #+#    #+#             */
/*   Updated: 2024/11/05 10:32:25 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	check_sign(const char *nptr, int *i, int *sign)
{
	if (nptr[*i] == '-')
	{
		*sign = -1;
		(*i)++;
	}
	else if (nptr[*i] == '+')
		(*i)++;
}

int	ft_atoi(const char *nptr)
{
	int	result;
	int	sign;
	int	i;
	int	trigger;

	i = 0;
	result = 0;
	sign = 1;
	trigger = 0;
	while (ft_isspace(nptr[i]))
		i++;
	check_sign(nptr, &i, &sign);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		trigger = 1;
		result = result * 10 + nptr[i] - 48;
		i++;
	}
	if (trigger == 0)
		return (INT_MAX);
	return (result * sign);
}
