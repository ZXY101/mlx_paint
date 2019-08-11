#ifndef MLX_PAINT_H
# define MLX_PAINT_H
# define FILL_COORD(C, X, Y) C.x = X, C.y = Y
# define FILL_RGB(RGB, R, G, B) RGB.r = R, RGB.g = G, RGB.b = B
# include "keydef.h"
# include "../libft/includes/libft.h"
# include <mlx.h>
# include <math.h>

typedef struct	s_line_math
{
	int			delta_x;
	int			delta_y;
	double		grad;
	double		q;
	double		iq;
}               t_line_math;

typedef struct  s_coord
{
    int x;
    int y;
}               t_coord;

typedef struct	s_rgb
{
	int			r;
	int			g;
	int			b;
}				t_rgb;

typedef struct	s_mlx_image
{
	void		*img_ptr;
	int			bpp;
	int			size_line;
	int			endian;
	char		*raw_data;
	int			width;
	int			height;
	t_coord 	pos;
}	            t_mlx_image;

typedef struct	s_environment
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_mlx_image	img;
	t_rgb		rgb;
	int			keys[512000];
	int			buttons[10];
    int         height;
    int         length;
}				t_environment;

/*
**Utility
*/

void			draw_line(t_coord c1, t_coord c2, t_mlx_image *img, t_rgb rgb);
int			    rgbtoi(int r, int g, int b);

/*
**Images
*/

void			pixel_put_image(t_mlx_image *img, int colour, int x, int y);
void			clear_image(t_mlx_image *img, int colour);
void			init_image(t_environment *env, t_mlx_image *img, int width, int height);
void			put_image(t_environment *env, t_mlx_image *img);

/*
**Hooks
*/

void			handle_hooks(void *win_ptr, t_environment *env);

/*
**Misc
*/

void			init_env(t_environment *env, char **av);

#endif