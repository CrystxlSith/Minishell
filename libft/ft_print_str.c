/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:19:01 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/06/07 11:53:17 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_str(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (print_str("(null)"));
	while (str[i])
		i += print_char((int)str[i]);
	return (i);
}
