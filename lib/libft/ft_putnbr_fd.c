/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:20:53 by amalgonn          #+#    #+#             */
/*   Updated: 2025/04/04 13:31:29 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	y;

	y = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		y = -n;
	}
	if (y > 9)
	{
		ft_putnbr_fd((y / 10), fd);
		ft_putnbr_fd((y % 10), fd);
	}
	else
		ft_putchar_fd((y + '0'), fd);
}
