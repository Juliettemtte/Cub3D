/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouette <jmouette@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:38:53 by hutzig            #+#    #+#             */
/*   Updated: 2025/02/26 15:35:54 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	clear_pixel_buffer(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->win_h)
	{
		x = 0;
		while (x < game->win_w)
		{
			game->render->pixels[y][x] = 0;
			x++;
		}
		y++;
	}
}

void	free_pixels(uint32_t **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}
