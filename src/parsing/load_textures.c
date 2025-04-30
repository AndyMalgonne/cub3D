/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 08:54:09 by amalgonn          #+#    #+#             */
/*   Updated: 2025/04/30 07:10:00 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	tex_params(t_data *data, int tmp_bpp, int tmp_ll, int tmp_end)
{
	if (tmp_bpp != data->textures->bpp || tmp_ll
		!= data->textures->line_len || tmp_end != data->textures->endian)
		return (printf("Error\nInconsistent texture parameters\n"), 0);
	return (1);
}

static int	load_single_texture(t_data *data, t_texture_data *tex_data)
{
	int	tmp_bpp;
	int	tmp_ll;
	int	tmp_end;

	*tex_data->img = mlx_xpm_file_to_image(data->mlx, tex_data->path,
			tex_data->width, tex_data->height);
	if (!*tex_data->img)
		return (printf("Error\nFailed to load texture: %s\n",
				tex_data->path), 0);
	*tex_data->addr = mlx_get_data_addr(*tex_data->img, &tmp_bpp, &tmp_ll,
			&tmp_end);
	if (!*tex_data->addr)
		return (printf("Error\nFailed to get data address for texture: %s\n",
				tex_data->path), 0);
	if (data->textures->bpp == 0)
	{
		data->textures->bpp = tmp_bpp;
		data->textures->line_len = tmp_ll;
		data->textures->endian = tmp_end;
	}
	else if (!tex_params(data, tmp_bpp, tmp_ll, tmp_end))
		return (0);
	return (1);
}

int	load_textures(t_data *data)
{
	t_texture_data	tex_data;

	tex_data = (t_texture_data){data->textures->no_path,
		&data->textures->no_img, &data->textures->no_addr,
		&data->textures->no_width, &data->textures->no_height};
	if (!load_single_texture(data, &tex_data))
		return (0);
	tex_data = (t_texture_data){data->textures->so_path,
		&data->textures->so_img, &data->textures->so_addr,
		&data->textures->so_width, &data->textures->so_height};
	if (!load_single_texture(data, &tex_data))
		return (0);
	tex_data = (t_texture_data){data->textures->we_path,
		&data->textures->we_img, &data->textures->we_addr,
		&data->textures->we_width, &data->textures->we_height};
	if (!load_single_texture(data, &tex_data))
		return (0);
	tex_data = (t_texture_data){data->textures->ea_path,
		&data->textures->ea_img, &data->textures->ea_addr,
		&data->textures->ea_width, &data->textures->ea_height};
	if (!load_single_texture(data, &tex_data))
		return (0);
	return (1);
}
