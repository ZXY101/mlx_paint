#include "../includes/mlx_paint.h"

int     main(int ac, char **av)
{
    t_environment env;
    init_env(&env, av, ac);

    handle_hooks(env.win_ptr, &env);
    mlx_loop(env.mlx_ptr);
    return (0);
}

