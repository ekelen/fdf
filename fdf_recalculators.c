# include "fdf.h"


double		get_center_y(t_ev *ev, double y_offset)
{
	double yctr;
	yctr = (ev->ymax - (ev->yrange / 2)) + y_offset;
	ev->offset_y = y_offset;
	ev->iso_ctr_y = yctr;
	return (yctr);
}

double		get_center_x(t_ev *ev, double x_offset)
{
	double xctr;
	xctr = (ev->xmax - (ev->xrange / 2)) + x_offset;
	ev->offset_x = x_offset;
	ev->iso_ctr_x = xctr;
	return (xctr);
}

int		fdf_offset(t_ev *ev, double off_x, double off_y)
{
	int i;
	int j;
	double osum;
	osum = 0;

	i = 0;
	j = 0;
	while (i < ev->iy)
	{
		j = 0;
		while (j < ev->ix)
		{
		 	
			(*ev).points[i][j].iso_x += off_x;
			(*ev).points[i][j].iso_y += off_y;
			j++;
		}
		i++;
	}
	return (1);
}

int		get_new_iso(t_ev *ev, double x_offset, double y_offset)
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
			(*ev).points[i][j].iso_x = ((*ev).points[i][j].ortho_x - (*ev).points[i][j].ortho_y) + x_offset;
			(*ev).points[i][j].iso_y = ((*ev).points[i][j].ortho_x + (*ev).points[i][j].ortho_y - ((*ev).points[i][j].float_z * ev->z_ratio)) - y_offset;
			j++;
		}
		i++;
	}
	
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
	ev->yrange = ev->ymax - ev->ymin;
	ev->xrange = ev->xmax - ev->xmin;
	return (1);
}

int		get_ortho_coords_from_scale(t_ev *ev)
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
			(*ev).points[i][j].ortho_x = (*ev).points[i][j].x * ev->ortho_scale;
			(*ev).points[i][j].ortho_y = (*ev).points[i][j].y * ev->ortho_scale;
			j++;
		}
		i++;
	}
	return (1);
}