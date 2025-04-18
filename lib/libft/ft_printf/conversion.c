/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:06:03 by amalgonn          #+#    #+#             */
/*   Updated: 2025/04/07 10:48:12 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	print_char(int fd, char c)
{
	ft_putchar_fd(c, fd);
	return (1);
}

int	print_string(int fd, const char *s)
{
	if (!s)
	{
		ft_putstr_fd("(null)", fd);
		return (6);
	}
	ft_putstr_fd(s, fd);
	return (ft_strlen(s));
}

static int	count_num(int n)
{
	int				i;
	unsigned int	y;

	i = 0;
	y = n;
	if (n < 0)
	{
		y = -n;
		i++;
	}
	while (y > 9)
	{
		y /= 10;
		i++;
	}
	return (++i);
}

int	print_num(int fd, int nb)
{
	ft_putnbr_fd(nb, fd);
	return (count_num(nb));
}
