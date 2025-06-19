/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouette <jmouette@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:40:36 by hutzig            #+#    #+#             */
/*   Updated: 2025/02/26 14:15:19 by jmouette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	game_events_release(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.action == MLX_RELEASE)
	{
		game->player->move_left = false;
		game->player->move_right = false;
		game->player->move_backward = false;
		game->player->move_forward = false;
		game->player->rotate_left = false;
		game->player->rotate_right = false;
	}
}

void	game_events(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		exit_game(game);
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_A)
			game->player->move_left = true;
		else if (keydata.key == MLX_KEY_D)
			game->player->move_right = true;
		else if (keydata.key == MLX_KEY_S)
			game->player->move_backward = true;
		else if (keydata.key == MLX_KEY_W)
			game->player->move_forward = true;
		else if (keydata.key == MLX_KEY_LEFT)
			game->player->rotate_left = true;
		else if (keydata.key == MLX_KEY_RIGHT)
			game->player->rotate_right = true;
		if (keydata.key == MLX_KEY_UP && game->render->brightness < 0.9)
			game->render->brightness += 0.1;
		else if (keydata.key == MLX_KEY_DOWN && game->render->brightness > 0)
			game->render->brightness -= 0.1;
	}
	game_events_release(keydata, game);
}

void	move_player(t_game *game)
{
	if (game->player->move_left)
		move_player_left(game);
	else if (game->player->move_right)
		move_player_right(game);
	else if (game->player->move_backward)
		move_player_backward(game);
	else if (game->player->move_forward)
		move_player_forward(game);
	else if (game->player->rotate_left)
		rotate_player_left(game, game->render);
	else if (game->player->rotate_right)
		rotate_player_right(game, game->render);
}
