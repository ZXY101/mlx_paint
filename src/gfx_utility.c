/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_utility.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stenner <stenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 11:13:27 by stenner           #+#    #+#             */
/*   Updated: 2019/08/12 15:46:23 by stenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_paint.h"

unsigned int			rgbtoi(int r, int g, int b)
{
	unsigned int rgb;

	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	if (r < 0)
		r = 0;
	if (g < 0)
		g = 0;
	if (b < 0)
		b = 0;
	rgb = 0x010000 * r + 0x000100 * g + b;
	return (rgb);
}

t_rgb	itorgb(unsigned int colour)
{
	t_rgb rgb;

	rgb.r = (colour & 0x00ff0000) >> 16;
	rgb.g = (colour & 0x0000ff00) >> 8;
	rgb.b = colour & 0x000000ff;
	return (rgb);
}

void ff(t_environment *env, t_coord begin, unsigned int colour, t_rgb rgb)
{
	t_coord points[4];

	points[0].y = begin.y + 1;
	points[0].x = begin.x;

	points[1].y = begin.y - 1;
	points[1].x = begin.x;

	points[2].y = begin.y;
	points[2].x = begin.x + 1;

	points[3].y = begin.y;
	points[3].x = begin.x - 1;

	if (begin.x >= 0 && begin.y >= 0 && begin.x < env->length && begin.y < env->height)
	{
		if (get_colour_image(&env->img, begin.x, begin.y) != colour || get_colour_image(&env->img, begin.x, begin.y) == rgbtoi(rgb.r, rgb.g, rgb.b))
			return ;
		pixel_put_image(&env->img, rgbtoi(rgb.r, rgb.g, rgb.b), begin.x, begin.y);
		//ff(env, points[0], colour, rgb);
		ff(env, points[1], colour, rgb);
		ff(env, points[2], colour, rgb); 
		ff(env, points[3], colour, rgb);
	}
}

void ff2(t_environment *env, t_coord begin, unsigned int colour, t_rgb rgb)
{
	t_coord points[4];

	points[0].y = begin.y + 1;
	points[0].x = begin.x;

	points[1].y = begin.y - 1;
	points[1].x = begin.x;

	points[2].y = begin.y;
	points[2].x = begin.x + 1;

	points[3].y = begin.y;
	points[3].x = begin.x - 1;

	if (begin.x >= 0 && begin.y >= 0 && begin.x < env->length && begin.y < env->height)
	{
		if (get_colour_image(&env->img, begin.x, begin.y) != colour || get_colour_image(&env->img, begin.x, begin.y) == rgbtoi(rgb.r, rgb.g, rgb.b))
			return ;
		pixel_put_image(&env->img, rgbtoi(rgb.r, rgb.g, rgb.b), begin.x, begin.y);
		ff2(env, points[0], colour, rgb);
		//ff(env, points[1], colour, rgb);
		ff2(env, points[2], colour, rgb); 
		ff2(env, points[3], colour, rgb);
	}
}

void flood_fill(t_environment *env, t_coord begin, t_rgb rgb, t_rgb replace)
{
	unsigned int colour;
	t_coord point;
	t_coord begin2;
	(void)point;
	(void)replace;
	FILL_COORD(begin2, begin.x, begin.y +1);
	colour = get_colour_image(&env->img, begin.x, begin.y);
	ff(env, begin, colour, rgb);
	ff2(env, begin2, colour, rgb);


}
