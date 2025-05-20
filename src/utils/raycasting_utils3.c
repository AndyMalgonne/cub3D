/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 04:23:17 by amalgonn          #+#    #+#             */
/*   Updated: 2025/05/20 04:24:24 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mray(t_data *data, t_ray *ray, int map_height)
{
	int	map_width;

	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
	if (ray->map_y < 0 || ray->map_y >= map_height || ray->map_x < 0)
		return (1);
	map_width = get_map_width(data, ray->map_y);
	if (ray->map_x >= map_width)
		return (1);
	if (data->map[ray->map_y][ray->map_x] == '1')
		return (1);
	return (0);
}
