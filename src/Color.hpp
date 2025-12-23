#ifndef _COLOR_HPP_
#define _COLOR_HPP_

#include "Vector3.hpp"
#include "utils.hpp"

#include <iostream>

f64 gamma_transform(const f64 linear_component) {return sqrt(linear_component);}

void write_color(const vec::Vector3_f64& pixel_color, const f64 samples_per_pixel)
{
    const Interval_f64 intensity(0., 0.999); 

    f64 r = pixel_color.x;
    f64 g = pixel_color.y;
    f64 b = pixel_color.z;

    r /= samples_per_pixel;
    g /= samples_per_pixel;
    b /= samples_per_pixel;

    r = gamma_transform(r);
    g = gamma_transform(g);
    b = gamma_transform(b);

    std::cout << static_cast<int>(256 * intensity.clamp(r)) << ' '
              << static_cast<int>(256 * intensity.clamp(g)) << ' '
              << static_cast<int>(256 * intensity.clamp(b)) << '\n';
}

#endif