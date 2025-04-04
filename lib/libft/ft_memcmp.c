/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:12:40 by amalgonn          #+#    #+#             */
/*   Updated: 2025/04/04 13:39:19 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((const unsigned char *)ptr1)[i] !=
		((const unsigned char *)ptr2)[i])
			return (((const unsigned char *)ptr1)[i] -
			((const unsigned char *)ptr2)[i]);
		i++;
	}
	return (0);
}
