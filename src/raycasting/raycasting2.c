/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:59:59 by amalgonn          #+#    #+#             */
/*   Updated: 2025/04/29 08:57:43 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_draw_range(t_data *data, t_ray *ray)
{
	int	line_height;

	line_height = (int)(data->win_height / ray->perp_wall_dist);
	ray->draw_start = -line_height / 2 + data->win_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = line_height / 2 + data->win_height / 2;
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

void	draw_vertical_line(t_data *data, int x, t_ray *ray)
{
	int		y;
	int		d;
	int		tex_y;
	int		color;

	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		d = y * 256 - data->win_height * 128
			+ (ray->draw_end - ray->draw_start + 1) * 128;
		tex_y = ((d * ray->tex_height)
				/ (ray->draw_end - ray->draw_start + 1)) / 256;
		if (ray->tex_x < 0 || ray->tex_x >= ray->tex_width || tex_y < 0
			|| tex_y >= ray->tex_height || !ray->texture)
			ft_error("Texture error");
		color = *(unsigned int *)(ray->texture + (tex_y
					* data->textures->line_len + ray->tex_x
					* (data->textures->bpp / 8)));
		if (x >= 0 && x < data->win_width && y >= 0 && y < data->win_height)
			my_mlx_pixel_put(data->img_addr,
				data->img_line_len, data->img_bpp, x, y, color);
		y++;
	}
}

void	draw_scene(t_data *data)
{
    int		ceiling_color;
    int		floor_color;
    int		x;
    t_ray	ray;
	
    ceiling_color = parse_color(data->ceiling);
    floor_color = parse_color(data->floor);
    fill_ceiling_and_floor(data, ceiling_color, floor_color);
    x = 0;
    while (x < data->win_width)
    {
        init_ray(data, x, &ray);
        calc_delta_dist(&ray);
        init_step(data, &ray);
        cast_ray(data, &ray);
        calc_perp_wall_dist(data, &ray);
        calc_draw_range(data, &ray);
        select_texture(data, &ray);
        calc_texture_x(data, &ray);
        draw_vertical_line(data, x, &ray);
        x++;
    }
}
