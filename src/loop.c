/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:48:40 by amalgonn          #+#    #+#             */
/*   Updated: 2025/05/20 06:13:49 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_close(t_data *data)
{
	cleanup(data);
	exit(0);
}

int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == 65307)
		handle_close(data);
	else if (keycode == 119)
		move_forward(data);
	else if (keycode == 115)
		move_backward(data);
	else if (keycode == 97)
		strafe_left(data);
	else if (keycode == 100)
		strafe_right(data);
	else if (keycode == 113 || keycode == 65361)
		rotate_left(data);
	else if (keycode == 101 || keycode == 65363)
		rotate_right(data);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, data->win_width, data->win_height);
	if (!data->img)
		(cleanup(data), printf("Error\nmlx_new_image failed\n"), exit(1));
	data->img_addr = mlx_get_data_addr(data->img, &data->img_bpp,
			&data->img_line_len, &data->img_endian);
	if (!data->img_addr)
		(cleanup(data), printf("Error\nmlx_get_data_addr failed\n"), exit(1));
	return (draw_scene(data),
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0), 0);
}

int	init_hooks(t_data *data)
{
	mlx_get_screen_size(data->mlx, &data->win_width, &data->win_height);
	data->win = mlx_new_window(data->mlx, data->win_width,
			data->win_height, "cub3D");
	if (!data->win)
	{
		printf("Error\nmlx_new_window failed\n");
		return (1);
	}
	mlx_hook(data->win, KeyPress, KeyPressMask, handle_keypress, data);
	mlx_hook(data->win, DestroyNotify, StructureNotifyMask, handle_close, data);
	return (0);
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
