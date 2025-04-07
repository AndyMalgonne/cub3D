/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:23:23 by amalgonn          #+#    #+#             */
/*   Updated: 2025/04/07 10:36:08 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_cub(char *file)
{
	int	i;

	i = ft_strlen(file);
	if (file[i - 1] != 'b' || file[i - 2] != 'u'
		|| file[i - 3] != 'c' || file[i - 4] != '.')
		return (printf("Error\nInvalid file extension\n"), 0);
	return (1);
}

int	check_walls(t_data *data)
{
	if (!check_top_wall(data))
		return (0);
	if (!check_bottom_wall(data))
		return (0);
	if (!check_left_and_right_walls(data))
		return (0);
	return (1);
}

int	check_map(t_data *data)
{
	if (!check_walls(data))
		return (0);
	if (!check_map_closed(data))
		return (0);
	return (1);
}
