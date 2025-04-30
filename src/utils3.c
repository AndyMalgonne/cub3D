/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:43:07 by amalgonn          #+#    #+#             */
/*   Updated: 2025/05/05 13:10:51 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_textures(t_data *data)
{
	if (!data->textures)
		return ;
	free(data->textures->no_path);
	free(data->textures->so_path);
	free(data->textures->ea_path);
	free(data->textures->we_path);
	if (data->mlx)
	{
		if (data->textures->no_img)
			mlx_destroy_image(data->mlx, data->textures->no_img);
		if (data->textures->so_img)
			mlx_destroy_image(data->mlx, data->textures->so_img);
		if (data->textures->ea_img)
			mlx_destroy_image(data->mlx, data->textures->ea_img);
		if (data->textures->we_img)
			mlx_destroy_image(data->mlx, data->textures->we_img);
	}
	free(data->textures);
	data->textures = NULL;
}

static void	free_mlx(t_data *data)
{
	if (!data->mlx)
		return ;
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	data->img = NULL;
	data->win = NULL;
	data->mlx = NULL;
}

void	cleanup(t_data *data)
{
	if (!data)
		return ;
	free_textures(data);
	free(data->ceiling);
	free(data->floor);
	free_map(data->map);
	free(data->game);
	data->ceiling = NULL;
	data->floor = NULL;
	data->map = NULL;
	data->game = NULL;
	free_mlx(data);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img_addr + (y * data->img_line_len + x * (data->img_bpp / 8));
	*(unsigned int *)dst = color;
}

void	fill_ceiling_and_floor(t_data *data, int cc, int fc)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->win_height / 2)
	{
		x = 0;
		while (x < data->win_width)
		{
			my_mlx_pixel_put(data, x, y, cc);
			x++;
		}
		y++;
	}
	while (y < data->win_height)
	{
		x = 0;
		while (x < data->win_width)
		{
			my_mlx_pixel_put(data, x, y, fc);
			x++;
		}
		y++;
	}
}
