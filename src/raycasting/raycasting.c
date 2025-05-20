/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:38:02 by amalgonn          #+#    #+#             */
/*   Updated: 2025/05/20 04:24:18 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_data *data, int x, t_ray *ray)
{
	double	camera_x;

	camera_x = 2 * x / (double)data->win_width - 1;
	ray->ray_dir_x = data->game->dir_x + data->game->plane_x * camera_x;
	ray->ray_dir_y = data->game->dir_y + data->game->plane_y * camera_x;
	ray->map_x = (int)data->game->pos_x;
	ray->map_y = (int)data->game->pos_y;
}

void	calc_delta_dist(t_ray *ray)
{
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

void	init_step(t_data *data, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->game->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->game->pos_x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->game->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->game->pos_y)
			* ray->delta_dist_y;
	}
}

void	cast_ray(t_data *data, t_ray *ray)
{
	int	hit;
	int	map_height;

	hit = 0;
	map_height = get_map_height(data);
	while (hit == 0)
	{
		hit = mray(data, ray, map_height);
	}
}

void	calc_perp_wall_dist(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
	{
		ray->perp_wall_dist = (ray->map_x - data->game->pos_x
				+ (1 - ray->step_x) / 2) / ray->ray_dir_x;
	}
	else
	{
		ray->perp_wall_dist = (ray->map_y - data->game->pos_y
				+ (1 - ray->step_y) / 2) / ray->ray_dir_y;
	}
}
