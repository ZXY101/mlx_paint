/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_utility.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stenner <stenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 11:13:27 by stenner           #+#    #+#             */
/*   Updated: 2019/08/16 12:20:22 by stenner          ###   ########.fr       */
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

t_coord	stack[1000000];
int		top = -1;


void push(t_coord x)
{
	stack[++top] = x; 
}

t_coord pop()
{
	return stack[top--];
}

int	is_empty()
{
	return (top == -1);
}

void flood_fill(t_environment *env, t_coord begin, t_rgb rgb, t_rgb replace)
{
	static const int dx[4] = {0, 1, 0, -1};
	static const int dy[4] = {-1, 0, 1, 0};

	if (rgbtoi(rgb.r, rgb.g, rgb.b) == rgbtoi(replace.r, replace.g, replace.b))
		return;
	push(begin);
	while (!is_empty())
	{
		t_coord p;
		p = pop();
		pixel_put_image(&env->img, rgbtoi(rgb.r, rgb.g, rgb.b), p.x, p.y);
		for (int i = 0; i < 4; i++)
		{
			t_coord np;
			np.x = p.x + dx[i];
			np.y = p.y + dy[i];
			if (np.x >= 0 && np.x < env->length && np.y >= 0 && np.y < env->height && get_colour_image(&env->img, np.x, np.y) ==  rgbtoi(replace.r, replace.g, replace.b))
			{
				push(np);
			}
		}
	}


}
