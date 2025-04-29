/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:48:40 by amalgonn          #+#    #+#             */
/*   Updated: 2025/04/29 10:30:14 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int handle_close(t_data *data)
{
    cleanup(data);
    exit(0);
}

int handle_keypress(int keycode, t_data *data) {
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
    if (!data->img) {
        cleanup(data);
        printf("Error\nmlx_new_image failed\n");
        exit(1);
    }
    data->img_addr = mlx_get_data_addr(data->img, &data->img_bpp,
            &data->img_line_len, &data->img_endian);
    if (!data->img_addr) {
        cleanup(data);
        printf("Error\nmlx_get_data_addr failed\n");
        exit(1);
    }
    draw_scene(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    return (0);
}

int	init_hooks(t_data *data)
{
	mlx_get_screen_size(data->mlx, &data->win_width, &data->win_height);
	data->win = mlx_new_window(data->mlx, data->win_width,
			data->win_height, "cub3D Textures Test");
	if (!data->win)
	{
		printf("Error\nmlx_new_window failed\n");
		return (1);
	}
	mlx_hook(data->win, KeyPress, KeyPressMask, handle_keypress, data);
	mlx_hook(data->win, DestroyNotify, StructureNotifyMask, handle_close, data);
	return (0);
}
