/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stenner <stenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 11:59:01 by stenner           #+#    #+#             */
/*   Updated: 2019/07/17 14:38:36 by stenner          ###   ########.fr       */
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

/*
**All of the hooks
*/

static int	fun(t_environment *env)
{
	(void)env;
	return (0);
}

void		handle_hooks(void *win_ptr, t_environment *env)
{
	mlx_hook(win_ptr, 2, 1L, key_down, env);
	mlx_hook(win_ptr, 3, 2L, key_release, env);
	mlx_hook(win_ptr, 4, 3L, mouse_down, env);
	mlx_hook(win_ptr, 5, 4L, mouse_release, env);
	mlx_hook(win_ptr, 17, 5L, finish, env);
	mlx_loop_hook(env->mlx_ptr, fun, env);
}
