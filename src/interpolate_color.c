#include "rasterize.h"

uint32_t	color_lerp(uint32_t start, uint32_t end, double lerp)
{
	t_color	s;
	t_color	e;
	t_color	ret;

	if (start == end)
		return (start);
	s.value = start;
	e.value = end;
	ret.ch.r = s.ch.r + (uint8_t)(lerp * (e.ch.r - s.ch.r));
	ret.ch.g = s.ch.g + (uint8_t)(lerp * (e.ch.g - s.ch.g));
	ret.ch.b = s.ch.b + (uint8_t)(lerp * (e.ch.b - s.ch.b));
	ret.ch.a = s.ch.a + (uint8_t)(lerp * (e.ch.a - s.ch.a));
	return (ret.value);
}

