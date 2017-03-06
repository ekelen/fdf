# include "fdf.h"


int		launch_mlx(t_ev *ev, t_pt **points)
{
	int i;
	int j;

	ev->mlx = mlx_init();
	ev->win = mlx_new_window(ev->mlx, WIDTH, HEIGHT, "EH MEH LEEX @ 42");

	j = 0;
	i = 0;
	while (i < ev->y_height)
	{
		j = 0;
		while (j <= ev->x_len && points[i][j].x >= 0)
		{
			mlx_pixel_put(ev->mlx, ev->win, points[i][j].iso_x, points[i][j].iso_y, 0x00FF0F);
			//printf("points[%d][%d] = (%f, %f)\n", i, j, points[i][j].iso_x, points[i][j].iso_y);
			if (points[i][j + 1].x >= 0)
			{
				//printf("Draws a line on X axis between:\n[%d][%d] = (%.0f, %.f) and (%.f, %.f)\n", i, j, points[i][j].iso_x, points[i][j].iso_y, points[i][j + 1].iso_x, points[i][j + 1].iso_y);
				draw(ev, points[i][j], points[i][j + 1]);
			}
			if (i < ev->y_height - 1)
			{
				//printf("Draws a line on Y axis between:\n[%d][%d] = (%.f, %.f) and (%.f, %.f)\n", i, j, points[i][j].iso_x, points[i][j].iso_y, points[i + 1][j].iso_x, points[i + 1][j].iso_y);
				draw(ev, points[i][j], points[i + 1][j]);
			}
			j++;
		}
		i++;
	}
	//mlx_key_hook(ev->win, my_key_function, 0);
	mlx_loop(ev->mlx);
	return (1);
}
