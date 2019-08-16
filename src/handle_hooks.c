/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stenner <stenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 11:59:01 by stenner           #+#    #+#             */
/*   Updated: 2019/08/16 12:27:29 by stenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**This c file has all of the functions that handle events
*/

#include "../includes/mlx_paint.h"

/*
**Quit the program when the close button is clicked
*/

static int	finish(void *none)
{
	(void)none;
	exit(0);
}

int		key_down(int key, t_environment *env)
{
	if (key == MLX_ESC)
		exit(0);
	if (key == 82)
		FILL_RGB(env->rgb, 255, 255, 255);
	if (key == 65)
		FILL_RGB(env->rgb, 0, 0, 0);
	if (key == 51)
		clear_image(&env->img, 0x000000);
	env->keys[key] = 1;
	return (0);
}

int		key_release(int key, t_environment *env)
{
	env->keys[key] = 0;
	return (0);
}



int		mouse_down(int key, int x, int y, t_environment *env)
{
	(void)x;
	(void)y;
	t_coord begin;
	FILL_COORD(begin, x, y);
	if (key == 3)
		flood_fill(env, begin, env->rgb, itorgb(get_colour_image(&env->img, begin.x, begin.y)));
	if (key == 1)
	{
		env->ox = x;
		env->oy = y;
		pixel_put_image(&env->img, rgbtoi(env->rgb.r, env->rgb.g, env->rgb.b), x, y);
		put_image(env, env->win_ptr, &env->img);
	}
	if (key == 2)
	{
		env->ox = x;
		env->oy = y;
		pixel_put_image(&env->img, rgbtoi(env->black.r, env->black.g, env->black.b), x, y);
		put_image(env, env->win_ptr, &env->img);
	}
	
	env->buttons[key] = 1;
	return (0);
}

int		mouse_release(int key, int x, int y, t_environment *env)
{
	(void)x;
	(void)y;
	env->buttons[key] = 0;
	return (0);
}

int		mouse_move(int x, int y, t_environment *env)
{
	if (env->buttons[1] == 1)
	{
		FILL_COORD(env->a, env->ox, env->oy);
		FILL_COORD(env->b, x, y);
		draw_line(env->a, env->b, &env->img, env->rgb);
		env->ox = x;
		env->oy = y;
	}
	if (env->buttons[2] == 1)
	{
		FILL_COORD(env->a, env->ox, env->oy);
		FILL_COORD(env->b, x, y);
		draw_line(env->a, env->b, &env->img, env->black);
		env->ox = x;
		env->oy = y;
	}

	return (0);
}
/*
**All of the hooks
*/
void	rgb_keys(t_environment *env)
{
	env->rgb.r += env->keys[86] && env->rgb.r < 255 ? 5 : 0;
	env->rgb.g += env->keys[87] && env->rgb.g < 255 ? 5 : 0;
	env->rgb.b += env->keys[88] && env->rgb.b < 255 ? 5 : 0;
	env->rgb.r -= env->keys[83] && env->rgb.r > 0 ? 5 : 0;
	env->rgb.g -= env->keys[84] && env->rgb.g > 0 ? 5 : 0;
	env->rgb.b -= env->keys[85] && env->rgb.b > 0 ? 5 : 0;
	env->rgb.r = env->rgb.r > 255 ? 255 : env->rgb.r;
	env->rgb.g = env->rgb.g > 255 ? 255 : env->rgb.g;
	env->rgb.b = env->rgb.b > 255 ? 255 : env->rgb.b;
	env->rgb.r = env->rgb.r < 0 ? 0 : env->rgb.r;
	env->rgb.g = env->rgb.g < 0 ? 0 : env->rgb.g;
	env->rgb.b = env->rgb.b < 0 ? 0 : env->rgb.b;
}

static int	fun(t_environment *env)
{
	rgb_keys(env);
	clear_image(&env->cd_img, rgbtoi(env->rgb.r, env->rgb.g, env->rgb.b));
	put_image(env, env->cd_win, &env->cd_img);
	put_image(env, env->win_ptr, &env->img);
	return (0);
}

void		handle_hooks(void *win_ptr, t_environment *env)
{
	mlx_hook(win_ptr, 2, 1L, key_down, env);
	mlx_hook(win_ptr, 3, 2L, key_release, env);
	mlx_hook(win_ptr, 4, 3L, mouse_down, env);
	mlx_hook(win_ptr, 5, 4L, mouse_release, env);
	mlx_hook(win_ptr, 6, 5L, mouse_move, env);
	mlx_hook(win_ptr, 17, 6L, finish, env);
	mlx_loop_hook(env->mlx_ptr, fun, env);
}
