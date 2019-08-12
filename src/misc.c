#include "../includes/mlx_paint.h"

void	init_env(t_environment *env, char **av, int ac)
{
	env->mlx_ptr = mlx_init();
	if (ac == 1)
    {
		env->height = 500;
    	env->length = 500;
	}
	else if (ac == 3)
	{
		env->length = ft_atoi(av[1]);
		env->height = ft_atoi(av[2]);
	}
	env->cd_win = mlx_new_window(env->mlx_ptr, 200, 200, "Colour");
	env->win_ptr = mlx_new_window(env->mlx_ptr, env->length, env->height, "MLX Paint v0.1");
	init_image(env, &env->img, env->length, env->height);
	init_image(env, &env->cd_img, 200, 200);
	FILL_RGB(env->rgb, 255, 255, 255);
	FILL_RGB(env->black, 0, 0, 0);
}
