#include "transform.h"

static t_vecd project(t_vecd v, t_transform *T);

t_vecd vecd(int x, int y, int z)
{
    return (t_vecd){(double)x, (double)y, (double)z};
}

t_vecd calculate_center(t_line *lines, int num_lines)
{
    double sum_x = 0, sum_y = 0, sum_z = 0;
    int count = 0;

	int	i;
	i = 0;
	while (i < num_lines)
    {
        sum_x += lines[i].x0 + lines[i].x1;
        sum_y += lines[i].y0 + lines[i].y1;
        sum_z += lines[i].z0 + lines[i].z1;
        count += 2;
		i++;
    }
    return (t_vecd){sum_x / count, sum_y / count, sum_z / count};
}

static t_vecd translate_to_origin(t_vecd v, t_vecd center)
{
    v.x -= center.x;
    v.y -= center.y;
    v.z -= center.z;
    return v;
}

static t_vecd translate_back(t_vecd v, t_vecd center)
{
    v.x += center.x;
    v.y += center.y;
    v.z += center.z;
    return v;
}

static t_vecd rotate(t_vecd vec, t_vector rotation)
{
    double rad_x = rotation.x * M_PI / 180.0;
    double rad_y = rotation.y * M_PI / 180.0;
    double rad_z = rotation.z * M_PI / 180.0;

    double sin_x = sin(rad_x), cos_x = cos(rad_x);
    double sin_y = sin(rad_y), cos_y = cos(rad_y);
    double sin_z = sin(rad_z), cos_z = cos(rad_z);

    double y1 = vec.y * cos_x - vec.z * sin_x;
    double z1 = vec.y * sin_x + vec.z * cos_x;
    double x2 = vec.x * cos_y + z1 * sin_y;
    double z2 = -vec.x * sin_y + z1 * cos_y;
    double x3 = x2 * cos_z - y1 * sin_z;
    double y3 = x2 * sin_z + y1 * cos_z;
    return (t_vecd){x3, y3, z2};
}

static t_vecd project(t_vecd v, t_transform *T)
{
    double iso_x;
    double iso_y;
    double scaled_iso_x;
    double scaled_iso_y;

    iso_x = (v.x - v.y) * cos(45 * M_PI / 180.0);
    iso_y = (v.x + v.y) * sin(45 * M_PI / 180.0) - v.z;
    scaled_iso_x = (double)T->scale / (double)10 * iso_x;
    scaled_iso_y = (double)T->scale / (double)10 * iso_y;
    v.x = T->offset_x + scaled_iso_x;
    v.y = T->offset_y + scaled_iso_y;
    return v;
}

t_line transform(t_line line, t_transform *T, t_vecd center)
{
    t_vecd u;
    t_vecd v;

    u = vecd(line.x0, line.y0, line.z0);
    v = vecd(line.x1, line.y1, line.z1);
    u = translate_to_origin(u, center);
    v = translate_to_origin(v, center);
    u = rotate(u, T->rotation);
    v = rotate(v, T->rotation);
    u = translate_back(u, center);
    v = translate_back(v, center);
    u = project(u, T);
    v = project(v, T);
    line.x0 = (int)round(u.x);
    line.y0 = (int)round(u.y);
    line.z0 = (int)round(u.z);
    line.x1 = (int)round(v.x);
    line.y1 = (int)round(v.y);
    line.z1 = (int)round(v.z);
    return (line);
}
