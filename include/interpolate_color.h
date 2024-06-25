#ifndef INTERPOLATE_COLOR_H
# define INTERPOLATE_COLOR_H

# include <stdint.h>
# include <math.h>

extern uint32_t	interpolate_color(uint32_t start, uint32_t end, double lerp);

typedef union u_color {
    struct {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    } ch;
    uint32_t value;
} t_color;

#endif /* INTERPOLATE_COLOR_H */
