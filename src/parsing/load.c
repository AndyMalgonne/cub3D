/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:59:59 by amalgonn          #+#    #+#             */
/*   Updated: 2025/04/21 16:27:47 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_number(const char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	validate_and_trim_rgb(char **rgb)
{
	int		i;
	char	*trimmed;

	i = 0;
	while (i < 3)
	{
		trimmed = ft_trim(rgb[i]);
		free(rgb[i]);
		rgb[i] = trimmed;
		if (!is_valid_number(rgb[i]))
			return (ft_fsplit(rgb),
				printf("Error\nColor values must be digits only\n"), 0);
		i++;
	}
	return (1);
}

int	parse_color(char *line)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;
	int		color;

	line = ft_trim(line);
	rgb = ft_split(line, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (ft_fsplit(rgb), printf("Error\nInvalid color format\n"), -1);
	if (!validate_and_trim_rgb(rgb))
		return (-1);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (ft_fsplit(rgb),
			printf("Error\nColor values must be between 0 and 255\n"), -1);
	color = (r << 16) | (g << 8) | b;
	return (ft_fsplit(rgb), color);
}

int load_textures(t_data *data)
{
	int temp_bpp, temp_line_len, temp_endian;
	data->textures->no_img = mlx_xpm_file_to_image(data->mlx, data->textures->no_path,
												&data->textures->no_width, &data->textures->no_height);
	if (!data->textures->no_img)
		return (printf("Error\nFailed to load texture: NO (%s)\n", data->textures->no_path), 0);
	data->textures->no_addr = mlx_get_data_addr(data->textures->no_img, &data->textures->bpp,
											&data->textures->line_len, &data->textures->endian);
	if (!data->textures->no_addr)
		return (printf("Error\nFailed to get data address for NO texture\n"), 0);
	data->textures->so_img = mlx_xpm_file_to_image(data->mlx, data->textures->so_path,
												&data->textures->so_width, &data->textures->so_height);
	if (!data->textures->so_img)
		return (printf("Error\nFailed to load texture: SO (%s)\n", data->textures->so_path), 0);
	data->textures->so_addr = mlx_get_data_addr(data->textures->so_img, &temp_bpp,
											&temp_line_len, &temp_endian);
	if (!data->textures->so_addr)
		return (printf("Error\nFailed to get data address for SO texture\n"), 0);
	if (temp_bpp != data->textures->bpp || temp_line_len != data->textures->line_len ||
		temp_endian != data->textures->endian)
		return (printf("Error\nInconsistent texture parameters for SO\n"), 0);
	data->textures->we_img = mlx_xpm_file_to_image(data->mlx, data->textures->we_path,
												&data->textures->we_width, &data->textures->we_height);
	if (!data->textures->we_img)
		return (printf("Error\nFailed to load texture: WE (%s)\n", data->textures->we_path), 0);
	data->textures->we_addr = mlx_get_data_addr(data->textures->we_img, &temp_bpp,
											&temp_line_len, &temp_endian);
	if (!data->textures->we_addr)
		return (printf("Error\nFailed to get data address for WE texture\n"), 0);
	if (temp_bpp != data->textures->bpp || temp_line_len != data->textures->line_len ||
		temp_endian != data->textures->endian)
		return (printf("Error\nInconsistent texture parameters for WE\n"), 0);
	data->textures->ea_img = mlx_xpm_file_to_image(data->mlx, data->textures->ea_path,
												&data->textures->ea_width, &data->textures->ea_height);
	if (!data->textures->ea_img)
		return (printf("Error\nFailed to load texture: EA (%s)\n", data->textures->ea_path), 0);
	data->textures->ea_addr = mlx_get_data_addr(data->textures->ea_img, &temp_bpp,
											&temp_line_len, &temp_endian);
	if (!data->textures->ea_addr)
		return (printf("Error\nFailed to get data address for EA texture\n"), 0);
	if (temp_bpp != data->textures->bpp || temp_line_len != data->textures->line_len ||
		temp_endian != data->textures->endian)
		return (printf("Error\nInconsistent texture parameters for EA\n"), 0);
	return (1);
}
