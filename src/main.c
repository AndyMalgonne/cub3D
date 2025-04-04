/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:17:46 by amalgonn          #+#    #+#             */
/*   Updated: 2025/04/04 11:27:49 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <stdlib.h>

void init_struct(t_data *data)
{
	data->no = NULL;
	data->so = NULL;
	data->ea = NULL;
	data->we = NULL;
	data->ceiling = NULL;
	data->floor = NULL;
	data->map = NULL;
}

int main(int argc, char **argv)
{
    t_data data;

    init_struct(&data);
    if (argc != 2)
        return (printf("Error\nInvalid number of arguments\n"), 1);
    if (!read_file(argv[1], &data))
        return (printf("Error\nFailed to read file\n"), 1);
    printf("NO: %s\n", data.no);
    printf("SO: %s\n", data.so);
    printf("EA: %s\n", data.ea);
    printf("WE: %s\n", data.we);
    printf("C: %s\n", data.ceiling);
    printf("F: %s\n", data.floor);
    printf("Map:\n%s\n", data.map);
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
