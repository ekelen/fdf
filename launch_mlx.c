# include "fdf.h"


static int		my_key_function(int keycode, t_ev *ev)
{
	printf("key event %d occured\n", keycode);
	mlx_pixel_put(MLX, WIN, 300, 300, 0x00FF0000);
	return (0);
}



int		launch_mlx(t_ev *ev)
{
	printf("Segfault ?");
	int x;
	int y;

	ev->mlx = mlx_init();
	ev->win = mlx_new_window(ev->mlx, WIDTH, HEIGHT, "EH MEH LEEX @ 42");

	x = 0;
	y = ev->origin_y;
	printf("ev->origin_y, %f\n", ev->origin_y);
	if (ev)
	{
		printf("he\n");
	if (ev->points)
	{
		printf("ha\n");
	if (ev->points[0])
	{
		printf("hi\n");
	if (ev->points[0][0])
	{
		printf("ho\n");
		if(ev->points[0][0].ortho_y)
			printf("hu\nev->points[0][0].ortho_y : %f\n", ev->points[0][0].ortho_y);
	}
}
}
}
/**
	while (y <= ev->offset_y)
	{
		x = ev->origin_x;
		while (x <= ev->offset_x)
		{
			printf("%f\n", ev->points[0][0]->ortho_y);
			printf("%f\n", ev->points[0][0]->ortho_y);

			//if (y == ev->points[x][y]->ortho_y && x == ev->points[x][y]->ortho_x)
			// 	mlx_pixel_put(ev->mlx, ev->win, x, y, 0x00FFFFFF);

			x += 1;
		}
		y += 1;
	}**/
	mlx_key_hook(ev->win, my_key_function, 0);
	mlx_loop(ev->mlx);
	return (1);
}
