#include "../includes/mlx_paint.h"

void	init_env(t_environment *env, char **av)
{
    (void)av;
	env->mlx_ptr = mlx_init();
    env->height = 500;
    env->length = 500;
	env->win_ptr = mlx_new_window(env->mlx_ptr, env->length, env->height, "MLX PAINT");
}