/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:21:12 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/06/07 11:53:30 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_nb(int nb)
{
	char	*str;
	int		len;

	str = ft_itoa(nb);
	len = print_str(str);
	free(str);
	return (len);
}
