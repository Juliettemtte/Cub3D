/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall_pixel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:41:34 by hutzig            #+#    #+#             */
/*   Updated: 2025/02/26 15:41:35 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	get_orientation(t_raycast *ray)
{	
	if (ray->direction.y < 0 && ray->boundary == 1)
		return (NORTH);
	if (ray->direction.y > 0 && ray->boundary == 1)
		return (SOUTH);
	if (ray->direction.x < 0 && ray->boundary == 0)
		return (WEST);
	if (ray->direction.x > 0 && ray->boundary == 0)
		return (EAST);
	return (EXIT_FAILURE);
}

// converts wall_x strip into a texture coordinate
// obs: when the wall faces SOUTH or WEST, the ray intersects from the opposite
// side of how the texture is naturally laid out. After the adjustment, the 
// leftmost part of the texture maps correctly to the left edge of the wall
static int	get_x_coordinate(t_raycast *ray, int txtr)
{
	int	x;

	x = (int)(ray->wall_x * TEXTURE);
	if (txtr == NORTH || txtr == EAST)
		return (x);
	if (txtr == SOUTH || txtr == WEST)
		return (TEXTURE - x - 1);
	return (EXIT_FAILURE);
}

//light source coming from the North-East (1, -1).
// Normalize the ray direction
// Normalize the light direction
// Compute dot product for shading
// Ensure min brightness (fmax with 0.5)
static double	get_shading_factor(t_raycast *ray, t_render *render)
{
	double	factor;
	double	dot_x;
	double	dot_y;

	ray->ray_length = sqrt(ray->direction.x * ray->direction.x
			+ ray->direction.y * ray->direction.y);
	ray->norm_ray.x = ray->direction.x / ray->ray_length;
	ray->norm_ray.y = ray->direction.y / ray->ray_length;
	ray->light_length = sqrt(render->light.x * render->light.x
			+ render->light.y * render->light.y);
	ray->norm_light.x = render->light.x / ray->light_length;
	ray->norm_light.y = render->light.y / ray->light_length;
	dot_x = ray->norm_ray.x * ray->norm_light.x;
	dot_y = ray->norm_ray.y * ray->norm_light.y;
	factor = dot_x + dot_y;
	factor = fmax(render->brightness, factor);
	return (factor);
}

// Reduce brightness of the color by factor (e.g., 0.6 = 60% brightness)
static uint32_t	apply_shading(uint32_t color, t_raycast *ray, t_render *render)
{
	uint8_t	a;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	double	factor;

	factor = get_shading_factor(ray, render);
	a = (color >> 24) & 0xFF;
	r = ((color >> 16) & 0xFF) * factor;
	g = ((color >> 8) & 0xFF) * factor;
	b = (color & 0xFF) * factor;
	return ((a << 24) | (r << 16) | (g << 8) | b);
}
// fixed light source coming from the North-East (1, -1).
// North-facing walls (d.y < 0) get more light.
// South-facing walls (d.y > 0) are darker.
// East-facing walls (d.x > 0) are brighter.
// West-facing walls (d.x < 0) are darker.

// get the pixels of the x wall strip from the corresponding texture;
// store them in the pixel_map
void	get_wall_pixels(t_game *game, t_raycast *ray, int x)
{
	int			t;
	int			tx;
	double		ty;
	double		scaling;
	uint32_t	color;

	t = get_orientation(ray);
	tx = get_x_coordinate(ray, t);
	scaling = (double)TEXTURE / fmax(ray->wx_height, 1.0);
	ty = (double)(ray->wx_top_pixel - game->win_h / 2 + ray->wx_height / 2)
		* scaling;
	while (ray->wx_top_pixel < ray->wx_bottom_pixel)
	{
		ty += scaling;
		color = game->render->txtr_buf[t][(TEXTURE * ((int)ty % TEXTURE)) + tx];
		color = apply_shading(color, ray, game->render);
		if (color > 0)
			game->render->pixels[ray->wx_top_pixel][x] = color;
		ray->wx_top_pixel++;
	}
}
