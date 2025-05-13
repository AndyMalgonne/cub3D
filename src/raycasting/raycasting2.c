/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:59:59 by amalgonn          #+#    #+#             */
/*   Updated: 2025/05/13 19:10:30 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_draw_range(t_data *data, t_ray *ray)
{
	ray->line_height = (int)(data->win_height / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + data->win_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + data->win_height / 2;
	if (ray->draw_end >= data->win_height)
		ray->draw_end = data->win_height - 1;
}

void	select_texture(t_data *data, t_ray *ray)
{
	if (ray->side == 0 && ray->ray_dir_x > 0)
	{
		ray->texture = data->textures->ea_addr;
		ray->tex_width = data->textures->ea_width;
		ray->tex_height = data->textures->ea_height;
	}
	else if (ray->side == 0 && ray->ray_dir_x < 0)
	{
		ray->texture = data->textures->we_addr;
		ray->tex_width = data->textures->we_width;
		ray->tex_height = data->textures->we_height;
	}
	else if (ray->side == 1 && ray->ray_dir_y > 0)
	{
		ray->texture = data->textures->so_addr;
		ray->tex_width = data->textures->so_width;
		ray->tex_height = data->textures->so_height;
	}
	else
	{
		ray->texture = data->textures->no_addr;
		ray->tex_width = data->textures->no_width;
		ray->tex_height = data->textures->no_height;
	}
}

void	calc_texture_x(t_data *data, t_ray *ray)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = data->game->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = data->game->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	ray->tex_x = (int)(wall_x * ray->tex_width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = ray->tex_width - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = ray->tex_width - ray->tex_x - 1;
}

static void	texture_draw(t_data *data, t_ray *ray, t_draw_data *params)
{
	int		tex_y;
	int		color;

	tex_y = (int)params->tex_pos;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= ray->tex_height)
		tex_y = ray->tex_height - 1;
	if (ray->tex_x < 0 || ray->tex_x >= ray->tex_width || !ray->texture)
		ft_error("Texture coordinate error");
	color = *(unsigned int *)(ray->texture
			+ (tex_y * data->textures->line_len
				+ ray->tex_x * (data->textures->bpp / 8)));
	if (params->x >= 0 && params->x < data->win_width
		&& params->y >= 0 && params->y < data->win_height)
		my_mlx_pixel_put(data, params->x, params->y, color);
}

void	draw_vertical_line(t_data *data, int x, t_ray *ray)
{
	int				y;
	double			tex_pos;
	double			step;
	t_draw_data		params;

	step = (double)ray->tex_height / ray->line_height;
	tex_pos = (ray->draw_start
			- data->win_height / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		params.x = x;
		params.y = y;
		params.tex_pos = tex_pos;
		texture_draw(data, ray, &params);
		tex_pos += step;
		y++;
	}
}
