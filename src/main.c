/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:17:46 by amalgonn          #+#    #+#             */
/*   Updated: 2025/04/18 14:56:22 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_struct(t_data *data)
{
	data->no = NULL;
	data->so = NULL;
	data->ea = NULL;
	data->we = NULL;
	data->ceiling = NULL;
	data->floor = NULL;
	data->map = NULL;
	data->flag = 0;
	data->img_height = 0;
	data->img_width = 0;
	data->win = NULL;
	data->win_height = 0;
	data->win_width = 0;
	data->mlx = mlx_init();
    if (!data->mlx)
	{
		printf("Error\nmlx_init failed\n");
		return (0);
	}
	return (1);
}

int init_game(t_data *data)
{
    data->game = malloc(sizeof(t_game));
    if (!data->game)
    {
        printf("Error\nFailed to allocate memory for game\n");
		return(0);
	}
    data->game->posX = 0;
    data->game->posY = 0;
    data->game->dirX = 0;
    data->game->dirY = 0;
    data->game->planeX = 0;
    data->game->planeY = 0;
    data->game->time = 0;
    data->game->oldtime = 0;
    return (1);
}

int	parsing(char *file, t_data *data, int *color_ceiling, int *color_floor)
{
	if (!read_file(file, data))
		return (0);
	if (!check_map(data))
		return (0);
	if (!check_color_texture_not_null(data))
		return (0);
	*color_ceiling = parse_color(data->ceiling);
	if (*color_ceiling == -1)
		return (0);
	*color_floor = parse_color(data->floor);
	if (*color_floor == -1)
		return (0);
	return (1);
}

void	my_mlx_pixel_put(char *addr, int line_length, int bpp, int x, int y, int color)
{
	char	*dst;

	dst = addr + (y * line_length + x * (bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_scene(t_data *data, char *img_addr, int line_len, int bpp)
{
	int x;
	for (x = 0; x < data->win_width; x++)
	{
		// Calculate ray position and direction
		double cameraX = 2 * x / (double)data->win_width - 1;
		double rayDirX = data->game->dirX + data->game->planeX * cameraX;
		double rayDirY = data->game->dirY + data->game->planeY * cameraX;

		// Current map square
		int mapX = (int)data->game->posX;
		int mapY = (int)data->game->posY;

		// Length of ray from one x/y side to next x/y side
		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		double sideDistX, sideDistY;

		// What direction to step in x or y
		int stepX, stepY;
		int hit = 0;
		int side;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (data->game->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - data->game->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (data->game->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - data->game->posY) * deltaDistY;
		}

		// Perform DDA
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (data->map[mapY][mapX] == '1')
				hit = 1;
		}

		// Calculate distance to the point of impact
		double perpWallDist;
		if (side == 0)
			perpWallDist = (mapX - data->game->posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - data->game->posY + (1 - stepY) / 2) / rayDirY;

		// Calculate height of line to draw
		int lineHeight = (int)(data->win_height / perpWallDist);
		int drawStart = -lineHeight / 2 + data->win_height / 2;
		if (drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + data->win_height / 2;
		if (drawEnd >= data->win_height) drawEnd = data->win_height - 1;

		// Pick color
		int color = (side == 1) ? 0xAAAAAA : 0xFFFFFF;

		// Draw the vertical stripe
		for (int y = drawStart; y < drawEnd; y++)
			my_mlx_pixel_put(img_addr, line_len, bpp, x, y, color);
	}
}


int	main(int argc, char **argv)
{
    t_data	data;
	t_img	img;
    int		color_ceiling;
    int		color_floor;

	if (argc != 2)
		return (printf("Error\nInvalid number of arguments\n"), 1);
	if (!init_struct(&data))
		return (printf("Error\ninit\n"), 1);
	if (!init_game(&data))
		return (printf("Error\ninit_game failed\n"), 1);
	if (!parsing(argv[1], &data, &color_ceiling, &color_floor))
		return (1);
	if (init_hooks(&data))
		return (printf("Error\ninit_hooks failed\n"), 1);
	if (!load_textures(&data))
		return (printf("Error\nload_textures failed\n"), 1);
	if (!get_player_position_and_direction(&data, data.game))
		return (0);
	img.img = mlx_new_image(data.mlx, data.win_width, data.win_height);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	draw_scene(&data, img.addr, img.line_len, img.bpp);
	mlx_put_image_to_window(data.mlx, data.win, img.img, 0, 0);
	mlx_loop(data.mlx);
	if (data.no)
        free(data.no);
    if (data.so)
        free(data.so);
    if (data.ea)
        free(data.ea);
    if (data.we)
        free(data.we);
    if (data.ceiling)
        free(data.ceiling);
    if (data.floor)
        free(data.floor);
    if (data.map)
        free(data.map);

    return (0);
}