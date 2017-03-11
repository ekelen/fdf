# include "fdf.h"



static int		update_iso_center(t_ev *ev)
{
	ev->iso_ctr_x = (ev->xmin + (ev->xrange / 2));
	ev->iso_ctr_y = (ev->ymin + (ev->yrange / 2));
	return (1);
}

static int		get_iso_dimensions(t_ev *ev)
{
	ev->yrange = fabs(ev->ymax - ev->ymin);
	ev->xrange = fabs(ev->xmax - ev->xmin);
	update_iso_center(ev);
	return (1);
}

int		get_xy_minmax(t_ev *ev)
{
	int i;
	int j;

	i = 0;
	j = 0;

	ev->xmin = ev->points[i][j].iso_x;
	ev->xmax = ev->points[i][j].iso_x;
	ev->ymax = ev->points[i][j].iso_y;
	ev->ymin = ev->points[i][j].iso_y;
	while (i < ev->iy)
	{
		j = 0;
		while (j < ev->ix)
		{
			if (ev->points[i][j].iso_x < ev->xmin)
				ev->xmin = ev->points[i][j].iso_x;
			if (ev->points[i][j].iso_x > ev->xmax)
				ev->xmax = ev->points[i][j].iso_x;
			if (ev->points[i][j].iso_y < ev->ymin)
				ev->ymin = ev->points[i][j].iso_y;
			if (ev->points[i][j].iso_y > ev->ymax)
				ev->ymax = ev->points[i][j].iso_y;
			j++;
		}
		i++;
	}
	get_iso_dimensions(ev);
	return (1);
}

int		get_new_iso(t_ev *ev)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (!ev)
		return(0);

	while (i < ev->iy)
	{
		j = 0;
		while (j < ev->ix)
		{
			(*ev).points[i][j].iso_x = ((*ev).points[i][j].ortho_x - (*ev).points[i][j].ortho_y);
			(*ev).points[i][j].iso_y = ((*ev).points[i][j].ortho_x + (*ev).points[i][j].ortho_y - ((*ev).points[i][j].float_z * ev->z_ratio));
			j++;
		}
		i++;
	}
	get_xy_minmax(ev);
	return (1);
}

int		get_ortho_coords(t_ev *ev)
{
	int i;
	int j;
	i = 0;
	j = 0;
	while (i < ev->iy)
	{
		j = 0;
		while (j < ev->ix)
		{
			(*ev).points[i][j].ortho_x = ((*ev).points[i][j].x * ev->ortho_scale) + ev->o_x_off;
			(*ev).points[i][j].ortho_y = ((*ev).points[i][j].y * ev->ortho_scale) + ev->o_y_off;
			j++;
		}
		i++;
	}
	return (1);
}