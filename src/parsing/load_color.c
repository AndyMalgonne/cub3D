/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:59:59 by amalgonn          #+#    #+#             */
/*   Updated: 2025/05/14 23:11:18 by amalgonn         ###   ########.fr       */
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

int	validate_rgb_array(char **rgb)
{
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		ft_fsplit(rgb);
		printf("Error\nInvalid color format\n");
		return (0);
	}
	if (!validate_and_trim_rgb(rgb))
		return (0);
	return (1);
}

int	convert_rgb_to_int(char **rgb)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		printf("Error\nColor values must be between 0 and 255\n");
		return (-1);
	}
	return ((r << 16) | (g << 8) | b);
}

int	parse_color(char *line)
{
	char	*trimmed_line;
	char	**rgb;
	int		color;
	int		len;

	if (!line)
		return (printf("Error\nNull color line\n"), -1);
	trimmed_line = ft_trim(line);
	if (!trimmed_line)
		return (printf("Error\nFailed to trim color line\n"), -1);
	len = ft_strlen(trimmed_line);
	if (len > 0 && trimmed_line[len - 1] == ',')
	{
		free(trimmed_line);
		return (printf("Error\nInvalid color format\n"), -1);
	}
	rgb = ft_split(trimmed_line, ',');
	free(trimmed_line);
	if (!rgb)
		return (printf("Error\nFailed to split color line\n"), -1);
	if (!validate_rgb_array(rgb))
		return (-1);
	color = convert_rgb_to_int(rgb);
	ft_fsplit(rgb);
	return (color);
}
