/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouette <jmouette@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:28:52 by jmouette          #+#    #+#             */
/*   Updated: 2025/02/26 14:25:31 by jmouette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// Read 4 bytes directly
uint32_t	get_pixel_color(int i, int j, mlx_texture_t *texture)
{
	int	index;

	index = (i * texture->width + j) * 4;
	return (*(uint32_t *)(texture->pixels + index));
}

int	set_texture_buffer(t_game *game, mlx_texture_t *texture, int orientation)
{
	uint32_t	*pixels;
	uint32_t	i;
	uint32_t	j;

	i = 0;
	pixels = ft_calloc(texture->height * texture->width, sizeof(uint32_t));
	if (!pixels)
		return (EXIT_FAILURE);
	while (i < texture->height)
	{
		j = 0;
		while (j < texture->width)
		{
			pixels[i * texture->width + j] = get_pixel_color(i, j, texture);
			j++;
		}
		i++;
	}
	game->render->txtr_buf[orientation] = pixels;
	return (EXIT_SUCCESS);
}

int	get_texture(t_game *game)
{
	game->txtr->no = mlx_load_png(game->data->no);
	game->txtr->so = mlx_load_png(game->data->so);
	game->txtr->we = mlx_load_png(game->data->we);
	game->txtr->ea = mlx_load_png(game->data->ea);
	if (!game->txtr->no || !game->txtr->so ||!game->txtr->we ||!game->txtr->ea)
		return (ft_putstr_fd("Error\nFailed to load txtr\n", 2), EXIT_FAILURE);
	if (set_texture_buffer(game, game->txtr->no, 0) == 1)
		return (EXIT_FAILURE);
	if (set_texture_buffer(game, game->txtr->so, 1) == 1)
		return (EXIT_FAILURE);
	if (set_texture_buffer(game, game->txtr->ea, 2) == 1)
		return (EXIT_FAILURE);
	if (set_texture_buffer(game, game->txtr->we, 3) == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
