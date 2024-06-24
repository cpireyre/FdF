#include "rasterize.h"

uint32_t	interpolate_color(uint32_t start, uint32_t end, int curr, int steps)
{
	t_color	s;
	t_color	e;
	t_color	ret;
	double	lerp;

	if (steps == 0 || start == end)
		return (start);
	s.value = start;
	e.value = end;
	lerp = (double)curr / (double)steps;
	ret.ch.r = s.ch.r + (uint8_t)(lerp * (e.ch.r - s.ch.r));
	ret.ch.g = s.ch.g + (uint8_t)(lerp * (e.ch.g - s.ch.g));
	ret.ch.b = s.ch.b + (uint8_t)(lerp * (e.ch.b - s.ch.b));
	ret.ch.a = s.ch.a + (uint8_t)(lerp * (e.ch.a - s.ch.a));
	return (ret.value);
}

