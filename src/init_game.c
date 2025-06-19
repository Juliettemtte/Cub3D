/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouette <jmouette@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:20:47 by jmouette          #+#    #+#             */
/*   Updated: 2025/02/26 16:38:47 by jmouette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	init_data(t_data *data)
{
	data->no = ft_calloc(256, sizeof(char));
	if (!data->no)
		return (ft_putstr_fd("Error : calloc failed for NO", 2), 1);
	data->so = ft_calloc(256, sizeof(char));
	if (!data->so)
		return (ft_putstr_fd("Error : calloc failed for SO", 2), 1);
	data->we = ft_calloc(256, sizeof(char));
	if (!data->we)
		return (ft_putstr_fd("Error : calloc failed for WE", 2), 1);
	data->ea = ft_calloc(256, sizeof(char));
	if (!data->ea)
		return (ft_putstr_fd("Error : calloc failed for EA", 2), 1);
	data->map = NULL;
	data->floor = 0;
	data->ceiling = 0;
	data->lines = 0;
	data->columns = 0;
	data->player_pos.x = 0;
	data->player_pos.y = 0;
	return (0);
}

int	init_render(t_game *game)
{
	int	i;

	game->render = ft_calloc(1, sizeof(t_render));
	if (!game->render)
		return (ft_putstr_fd("Error : calloc failed for game->render", 2), 1);
	game->render->pixels = ft_calloc(game->win_h + 1, sizeof(uint32_t *));
	if (!game->render->pixels)
		return (ft_putstr_fd("Memory allocation failed for pixels", 2), 1);
	i = 0;
	while (i < game->win_h)
	{
		game->render->pixels[i] = ft_calloc(game->win_w, sizeof(uint32_t));
		if (!game->render->pixels[i])
			return (ft_putstr_fd("Memory allocation failed for pixels", 2), 1);
		i++;
	}
	game->render->light.x = 1.0;
	game->render->light.y = -1.0;
	game->render->brightness = 0.5;
	return (EXIT_SUCCESS);
}

int	init_game(t_game *game)
{
	game->data = ft_calloc(1, sizeof(t_data));
	if (!game->data)
		return (ft_putstr_fd("Error : calloc failed for game->data", 2), 1);
	if (init_data(game->data) == 1)
		return (EXIT_FAILURE);
	game->win_w = WIDTH;
	game->win_h = HEIGHT;
	game->txtr = ft_calloc(1, sizeof(t_txtr));
	if (!game->txtr)
		return (ft_putstr_fd("Error : calloc failed for game->txtr", 2), 1);
	game->player = ft_calloc(1, sizeof(t_player));
	if (!game->player)
		return (ft_putstr_fd("Error : calloc failed for game->player", 2), 1);
	game->ray = ft_calloc(1, sizeof(t_raycast));
	if (!game->ray)
		return (ft_putstr_fd("Error : calloc failed for game->ray", 2), 1);
	if (init_render(game) == 1)
		return (EXIT_FAILURE);
	game->img = NULL;
	return (EXIT_SUCCESS);
}
