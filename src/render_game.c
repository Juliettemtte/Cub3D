/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouette <jmouette@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:38:53 by hutzig            #+#    #+#             */
/*   Updated: 2025/06/19 11:13:06 by jmouette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void draw_minimap(t_game *game);

void rendering_game(void *param)
{
    t_game *game;

    game = (t_game *)param;
    if (game->img)
        mlx_delete_image(game->mlx, game->img);
    clear_pixel_buffer(game);
    move_player(game);
    raycasting(game);
    game->img = mlx_new_image(game->mlx, game->win_w, game->win_h);
    if (!game->img)
        return;
    draw_minimap(game);
    rendering_image(game);
}

void raycasting(t_game *game)
{
    t_raycast *ray;
    int x;

    x = 0;
    ray = game->ray;
    while (x < game->win_w)
    {
        get_ray_direction(game, game->player, ray, x);
        get_delta_distance(game->player, ray);
        get_steps_distance(game->player, ray);
        get_wall_distance_and_height(game, ray);
        get_wall_projection_pixels(game, game->player, ray);
        get_wall_pixels(game, ray, x);
        x++;
    }
}

// process and render the whole image from the pixel map (screen pixels)
// check if the pixel is in wall, floor or ceiling position
void rendering_image(t_game *game)
{
    uint32_t color;
    uint32_t *pixels;
    uint32_t x;
    uint32_t y;

    color = 0;
    pixels = (uint32_t *)game->img->pixels;
    y = 0;
    while (y < (uint32_t)game->win_h)
    {
        x = 0;
        while (x < (uint32_t)game->win_w)
        {
            if (game->render->pixels[y][x] > 0)
                color = game->render->pixels[y][x];
            else if (y < (uint32_t)game->win_h / 2)
                color = game->data->ceiling;
            else if (y > (uint32_t)game->win_h / 2)
                color = game->data->floor;
            pixels[y * (uint32_t)game->win_w + x] = color;
            x++;
        }
        y++;
    }
    mlx_image_to_window(game->mlx, game->img, 0, 0);
}

#define MINIMAP_SCALE 12
#define MINIMAP_PADDING 12
#define WALL_COLOR 0x639021CA
#define FLOOR_COLOR 0x00000000
#define PLAYER_COLOR 0xD76FDEFF
#define CONE_COLOR 0x289021FF

void draw_square(t_game *game, int x, int y, int size, uint32_t color)
{
    int i, j;

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            int px = x + j;
            int py = y + i;
            if (px >= 0 && px < game->win_w && py >= 0 && py < game->win_h)
                game->render->pixels[py][px] = color;
        }
    }
}

void draw_minimap_background(t_game *game)
{
    int width = game->data->columns * MINIMAP_SCALE;
    int height = game->data->lines * MINIMAP_SCALE;
    int x = MINIMAP_PADDING - 2;
    int y = MINIMAP_PADDING - 2;

    draw_square(game, x, y, height + 4, 0x111111AA);
    for (int i = 0; i < height + 4; i++)
        draw_square(game, x, y + i, width + 4, 0x111111AA);
}

void draw_line(t_game *game, int x0, int y0, int x1, int y1, uint32_t color)
{
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    while (1)
    {
        if (x0 >= 0 && x0 < game->win_w && y0 >= 0 && y0 < game->win_h)
            game->render->pixels[y0][x0] = color;
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void fill_triangle(t_game *game, int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{
    if (y1 < y0)
    {
        int tmpx = x0, tmpy = y0;
        x0 = x1;
        y0 = y1;
        x1 = tmpx;
        y1 = tmpy;
    }
    if (y2 < y0)
    {
        int tmpx = x0, tmpy = y0;
        x0 = x2;
        y0 = y2;
        x2 = tmpx;
        y2 = tmpy;
    }
    if (y2 < y1)
    {
        int tmpx = x1, tmpy = y1;
        x1 = x2;
        y1 = y2;
        x2 = tmpx;
        y2 = tmpy;
    }

    int total_height = y2 - y0;
    if (total_height == 0)
        return;

    for (int i = 0; i < total_height; i++)
    {
        int second_half = i > y1 - y0 || y1 == y0;
        int segment_height = second_half ? y2 - y1 : y1 - y0;

        float alpha = (float)i / total_height;
        float beta = (float)(i - (second_half ? y1 - y0 : 0)) / segment_height;

        int ax = x0 + (x2 - x0) * alpha;
        int bx = second_half ? x1 + (x2 - x1) * beta : x0 + (x1 - x0) * beta;

        if (ax > bx)
        {
            int tmp = ax;
            ax = bx;
            bx = tmp;
        }

        for (int j = ax; j <= bx; j++)
        {
            if (j >= 0 && j < game->win_w && (y0 + i) >= 0 && (y0 + i) < game->win_h)
                game->render->pixels[y0 + i][j] = color;
        }
    }
}

void draw_minimap_view_cone(t_game *game)
{
    int cx = MINIMAP_PADDING + (int)(game->player->position.x * MINIMAP_SCALE);
    int cy = MINIMAP_PADDING + (int)(game->player->position.y * MINIMAP_SCALE);

    int cone_length = MINIMAP_SCALE * 2;
    int cone_width = MINIMAP_SCALE / 1.15;

    double dx = -game->player->d.x;
    double dy = -game->player->d.y;

    int tip_x = cx;
    int tip_y = cy;

    int base_center_x = cx - (int)(dx * cone_length);
    int base_center_y = cy - (int)(dy * cone_length);

    int perp_x = (int)(-dy * cone_width);
    int perp_y = (int)(dx * cone_width);

    int base_x1 = base_center_x + perp_x;
    int base_y1 = base_center_y + perp_y;
    int base_x2 = base_center_x - perp_x;
    int base_y2 = base_center_y - perp_y;

    fill_triangle(game, tip_x, tip_y, base_x1, base_y1, base_x2, base_y2, CONE_COLOR);
}

void draw_minimap(t_game *game)
{
    int row, col;
    char **map = game->data->map;
    int x, y;

    if (!map)
        return;
    draw_minimap_background(game);
    for (row = 0; map[row]; row++)
    {
        for (col = 0; map[row][col]; col++)
        {
            x = MINIMAP_PADDING + col * MINIMAP_SCALE;
            y = MINIMAP_PADDING + row * MINIMAP_SCALE;

            if (map[row][col] == '1')
                draw_square(game, x, y, MINIMAP_SCALE, WALL_COLOR);
            else if (map[row][col] == '0')
                draw_square(game, x, y, MINIMAP_SCALE, FLOOR_COLOR);
        }
    }

    int player_x = MINIMAP_PADDING + (int)(game->player->position.x * MINIMAP_SCALE);
    int player_y = MINIMAP_PADDING + (int)(game->player->position.y * MINIMAP_SCALE);
    draw_square(game, player_x - MINIMAP_SCALE / 2, player_y - MINIMAP_SCALE / 2, MINIMAP_SCALE, PLAYER_COLOR);

    draw_minimap_view_cone(game);
}
