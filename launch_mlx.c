# include "fdf.h"

static int		my_key_function(int keycode, t_ev *ev)
{
	printf("key event %d occured\n", keycode);
	mlx_pixel_put(MLX, WIN, 300, 300, 0x00FF0000);
	return (0);
}



int		launch_mlx(t_ev *ev)
{
	int x;
	int y;

	ev->mlx = mlx_init();
	ev->win = mlx_new_window(ev->mlx, WIDTH, HEIGHT, "EH MEH LEEX @ 42");
	ev->origin_x = (WIDTH / 2) - (ev->width / 2);
	ev->origin_y = (HEIGHT / 2) - (ev->height / 2);

	ev->offset_y = (HEIGHT / 2) + (ev->height / 2);
	ev->offset_x = (WIDTH / 2) + (ev->width / 2);

	y = ev->origin_y;
	while (y <= ev->offset_y)
	{
		x = ev->origin_x;
		while (x < ev->offset_x)
		{
			mlx_pixel_put(ev->mlx, ev->win, x, y, 0x00FFFFFF);		
			x += ev->padding;
		}
		y += ev->padding;
	}
	mlx_key_hook(ev->win, my_key_function, 0);
	mlx_loop(ev->mlx);
	return (1);
}