/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouette <jmouette@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:42:21 by jmouette          #+#    #+#             */
/*   Updated: 2025/06/19 10:58:46 by jmouette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "../MLX42/include/MLX42/MLX42.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <string.h>

#define WIDTH 1000
#define HEIGHT 600
#define TEXTURE 640
#define MOVE_SPEED 0.1
#define ROT_SPEED 0.07
#define EPS 0.1

typedef enum s_orientation
{
    NORTH,
    SOUTH,
    EAST,
    WEST,
} t_orientation;

typedef struct s_coord
{
    int x;
    int y;
} t_coord;

typedef struct s_coordd
{
    double x;
    double y;
} t_coordd;

typedef struct s_txtr
{
    mlx_texture_t *no;
    mlx_texture_t *ea;
    mlx_texture_t *so;
    mlx_texture_t *we;
    mlx_texture_t *ce;
    mlx_texture_t *fl;
} t_txtr;

typedef struct s_data
{
    char *no;
    char *so;
    char *we;
    char *ea;
    char **map;
    char **map_access;
    char dir_player;
    int lines;
    int columns;
    uint32_t floor;
    uint32_t ceiling;
    t_coord player_pos;
    t_coord map_size;
} t_data;

typedef struct s_player
{
    int view;
    bool move_left;
    bool move_right;
    bool move_backward;
    bool move_forward;
    bool rotate_left;
    bool rotate_right;
    t_coordd position;
    t_coordd d;
    t_coordd p;
} t_player;

typedef struct s_raycast
{
    double camera;
    double wall_x;
    double wx_distance;
    int wx_top_pixel;
    int wx_bottom_pixel;
    int wx_height;
    int boundary;
    t_coord map;
    t_coord step_dir;
    t_coordd step;
    t_coordd delta;
    t_coordd direction;
    double ray_length;
    double light_length;
    t_coordd norm_ray;
    t_coordd norm_light;
} t_raycast;

typedef struct s_render
{
    uint32_t *txtr_buf[4];
    uint32_t **pixels;
    t_coordd light;
    double brightness;
} t_render;

typedef struct s_game
{
    mlx_t *mlx;
    t_data *data;
    t_txtr *txtr;
    mlx_image_t *img;
    t_player *player;
    t_raycast *ray;
    t_render *render;
    int win_w;
    int win_h;
} t_game;

/* MAIN */
void rendering_game(void *param);

/* RAYCASTING */
void raycasting(t_game *game);
void get_ray_direction(t_game *game, t_player *player,
                       t_raycast *ray, int x);
void get_delta_distance(t_player *player, t_raycast *ray);
void get_steps_distance(t_player *player, t_raycast *ray);
void get_wall_distance_and_height(t_game *game, t_raycast *ray);
void get_wall_projection_pixels(t_game *game,
                                t_player *player, t_raycast *ray);

/* RENDERING */
void get_wall_pixels(t_game *game, t_raycast *ray, int x);
void rendering_image(t_game *game);

/* INIT_GAME */
int init_game(t_game *game);

/* GAME */
void game_events(mlx_key_data_t keydata, void *param);
void move_player(t_game *game);
void set_player(t_game *game, t_player *player);

/* MOVE_PLAYER */
void move_player_left(t_game *game);
void move_player_right(t_game *game);
void move_player_forward(t_game *game);
void move_player_backward(t_game *game);

/* ROTATE_PLAYER */
void rotate_player_right(t_game *game, t_render *r);
void rotate_player_left(t_game *game, t_render *r);

/* VALIDATE_CUB */
int validate_cub(char *map_name, t_game *game);
int validate_extension(char *map_name, char a, char b, char c);

/* MAP */
int is_map(char *s);
int empty_lines(char *line);
int copy_map(t_data *data, char **cub_content, int map_start, int i);

/* VALIDATE_MAP */
int valid_chars(t_data *data);

/* VALIDATE_WALLS */
int is_accessible(t_data *data);

/* VALIDATE_TEXTURES */
int validate_texture(char **map, t_game *game);

/* VALIDATE_RGB */
int validate_rgb(char **map, t_game *game);

/* UTILS_VALIDATE */
char *extract(char **map, int i, int j, char *extract);
int is_duplicate_rgb(uint32_t rbg_type);
uint32_t create_color(int r, int g, int b, int a);
int check_rgb(char *rgb);
int validate_rgb_split(char **rgb_split);

/* READ_MAP */
char **read_map(char *path);

/* IMAGES */
int get_texture(t_game *game);

/* FREE */
void clear_pixel_buffer(t_game *game);
void free_pixels(uint32_t **array);
void free_char_array(char **array);
void free_texture(t_game *game);
void free_game(t_game *game);
void exit_game(t_game *game);

#endif
