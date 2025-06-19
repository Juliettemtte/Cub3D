/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouette <jmouette@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:41:10 by jmouette          #+#    #+#             */
/*   Updated: 2025/02/26 14:10:55 by jmouette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	resize_window(int width, int height, void *param)
{
	int		i;
	t_game	*game;

	game = (t_game *)param;
	game->win_w = width;
	game->win_h = height;
	if (game->render->pixels)
		free_pixels(game->render->pixels);
	game->render->pixels = ft_calloc(game->win_h + 1, sizeof(uint32_t *));
	if (!game->render->pixels)
		return (ft_putstr_fd("Memory allocation failed for pixels", 2));
	i = 0;
	while (i < game->win_h)
	{
		game->render->pixels[i] = ft_calloc(game->win_w, sizeof(uint32_t));
		if (!game->render->pixels[i])
			return (ft_putstr_fd("Memory allocation failed for pixels row", 2));
		i++;
	}
	return ;
}

int	start_game(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!game->mlx)
		return (EXIT_FAILURE);
	set_player(game, game->player);
	mlx_key_hook(game->mlx, &game_events, game);
	mlx_loop_hook(game->mlx, &rendering_game, game);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nInvalid arguments.", 2);
		ft_putstr_fd("Please use the format './cub3D *.cub'\n", 2);
		return (EXIT_FAILURE);
	}
	if (init_game(&game) == 1)
		return (free_game(&game), EXIT_FAILURE);
	if (validate_cub(argv[1], &game) == 1)
		return (free_game(&game), EXIT_FAILURE);
	if (get_texture(&game) == 1)
		return (free_game(&game), EXIT_FAILURE);
	if (start_game(&game) == 1)
		return (exit_game(&game), EXIT_FAILURE);
	mlx_resize_hook(game.mlx, resize_window, &game);
	mlx_loop(game.mlx);
	exit_game(&game);
	return (EXIT_SUCCESS);
}
