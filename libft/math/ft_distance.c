#include <math.h>

double	ft_distance(int x0, int y0, int x1, int y1)
{
    return (sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1)));
}
