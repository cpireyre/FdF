#ifndef COLOR_LERP_H
# define COLOR_LERP_H

extern uint32_t	color_lerp(uint32_t start, uint32_t end, double lerp);

typedef union u_color {
    struct {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    } ch;
    uint32_t value;
} t_color;

#endif /* COLOR_LERP_H */
