/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouette <jmouette@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:47:33 by jmouette          #+#    #+#             */
/*   Updated: 2025/02/19 17:04:05 by jmouette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	rotate_player_right(t_game *game, t_render *r)
{
	t_player	*p;
	double		prev_dx;
	double		prev_px;
	double		prev_light_x;

	p = game->player;
	prev_dx = p->d.x;
	prev_px = p->p.x;
	p->d.x = p->d.x * cos(ROT_SPEED) - p->d.y * sin(ROT_SPEED);
	p->d.y = prev_dx * sin(ROT_SPEED) + p->d.y * cos(ROT_SPEED);
	p->p.x = p->p.x * cos(ROT_SPEED) - p->p.y * sin(ROT_SPEED);
	p->p.y = prev_px * sin(ROT_SPEED) + p->p.y * cos(ROT_SPEED);
	prev_light_x = r->light.x;
	r->light.x = r->light.x * cos(ROT_SPEED) - r->light.y * sin(ROT_SPEED);
	r->light.y = prev_light_x * sin(ROT_SPEED) + r->light.y * cos(ROT_SPEED);
}

void	rotate_player_left(t_game *game, t_render *r)
{
	t_player	*p;
	double		prev_dx;
	double		prev_px;
	double		prev_light_x;

	p = game->player;
	prev_dx = p->d.x;
	prev_px = p->p.x;
	p->d.x = p->d.x * cos(-ROT_SPEED) - p->d.y * sin(-ROT_SPEED);
	p->d.y = prev_dx * sin(-ROT_SPEED) + p->d.y * cos(-ROT_SPEED);
	p->p.x = p->p.x * cos(-ROT_SPEED) - p->p.y * sin(-ROT_SPEED);
	p->p.y = prev_px * sin(-ROT_SPEED) + p->p.y * cos(-ROT_SPEED);
	prev_light_x = r->light.x;
	r->light.x = r->light.x * cos(-ROT_SPEED) - r->light.y * sin(-ROT_SPEED);
	r->light.y = prev_light_x * sin(-ROT_SPEED) + r->light.y * cos(-ROT_SPEED);
}
