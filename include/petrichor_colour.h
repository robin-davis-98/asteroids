#ifndef PET_COLOUR_H
#define PET_COLOUR_H

#include <cstdint>
#include <petrichor_math.h>

union Colour
{
    struct {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    };
    uint32_t raw;
};

inline Colour colour_from_rbga(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
   Colour c;
    c.r = r;
    c.g = g;
    c.b = b;
    c.a = a;
    return c;
}

inline Colour colour_from_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    return colour_from_rbga(r, g, b, 255);
}

inline Colour colour_from_u32(uint32_t hex) {
    Colour c;
    c.raw = hex;
    return c;
}

inline Vec4 colour_to_normalized(Colour c) {
    return {
        c.r / 255.0f,
        c.g / 255.0f,
        c.b / 255.0f,
        c.a / 255.0f
    };
}
#endif