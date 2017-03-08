# include "fdf.h"


static int		resize_to_fit(t_ev *ev)
{
	double overflow_x;
	double overflow_y;
	double scale;
	int i;
	int j;

	i = 0;
	j = 0;
	overflow_x = (ev->sw / fabs(ev->xmax - ev->xmin));
	overflow_y = (ev->sh / fabs(ev->ymax - ev->ymin));
	scale = overflow_x < overflow_y ? overflow_x : overflow_y;
	while (i < ev->iy)
	{
		j = 0;
		while (j < ev->ix)
		{
			(*ev).points[i][j].iso_x *= scale;
			(*ev).points[i][j].iso_y *= scale;
			j++;
		} 
		i++;
	}
	return (1);
}


static int		get_init_projection(t_ev *ev)
{
	int i;
	int j;
	double off_x;
	double off_y;

	i = 0;
	j = 0;

	get_ortho_coords_from_scale(ev);
	get_new_iso(ev);
	get_xy_minmax(ev);
	if (ev->xmax - ev->xmin > ev->sw || ev->ymax - ev->ymin > ev->sh)
		resize_to_fit(ev);
	off_x = (MARGIN / 2) + fabs(ev->xmin) + ((ev->sh - ev->xrange) / 2);
	off_y = (MARGIN / 2) + fabs(ev->ymin) + ((ev->sh - ev->yrange) / 2);
	fdf_offset(ev, off_x, off_y);
	get_center(ev);
	launch_mlx(ev);
	return (1);
}


static int		get_z_minmax(t_ev *ev)
{
	int j;
	int i;
	ev->z_max = ev->points[0][0].z;
	ev->z_min = ev->points[0][0].z;

	j = 0;
	i = 0;
	while (i < ev->iy)
	{
		j = 0;
		while (j < ev->ix)
		{
			if (ev->points[i][j].z > ev->z_max)
				ev->z_max = ev->points[i][j].z;
			if (ev->points[i][j].z < ev->z_min)
				ev->z_min = ev->points[i][j].z;
				j++;
		}
		i++;
	}
	ev->ortho_scale = ev->sw / (ev->ix + ev->iy);
	if (!(ev->z_range = ft_extra_abs(ev->z_max - ev->z_min)))
		ev->z_ratio = 0;
	else
		ev->z_ratio = ev->sw / (ev->z_range * ev->ortho_scale);
	//printf("z_max : %f\nz_min: %f\nz_range : %f\nz_ratio : %f\n", ev->z_max, ev->z_min, ev->z_range, ev->z_ratio);
	get_init_projection(ev);
	return (1);
}

int		map_init(char **strmap, t_ev *ev)
{
	int i;
	int j;
	char **row;

	ev->points = (t_pt **)malloc(sizeof(t_pt *) * ev->iy);
	i = 0;
	j = 0;
	while (i < ev->iy)
	{
		j = 0;
		row = ft_strsplit(strmap[i], ' ');
		while (row[j])
			j++;
		ev->points[i] = (t_pt *)malloc(sizeof(t_pt) * j);
		j = 0;
		while (row[j])
		{
			point_init(&ev->points[i][j], row[j], i, j);
			free(row[j]);
			j++;
		}
		ev->ix = j;
		i++;
	}
	get_z_minmax(ev);
	free(row);
	return (1);
}
