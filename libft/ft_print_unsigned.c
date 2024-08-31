/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:17:36 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/06/07 11:53:07 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_unsigned(unsigned int nb)
{
	char	*str;
	int		len;

	str = ft_uitoa(nb);
	len = print_str(str);
	free(str);
	return (len);
}
