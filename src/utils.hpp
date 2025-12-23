#ifndef _UTILS_HPP_
#define _UTILS_HPP_



#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>


typedef char            i8;
typedef unsigned char   u8;
typedef short           i16;
typedef unsigned short  u16;
typedef int             i32;
typedef unsigned int    u32;
typedef float           f32;
typedef double          f64;

// i32 x = 0x7fff;

// Constants
const f64 INF = std::numeric_limits<f64>::infinity();
const f64 PI = 3.1415926535897932385;

// Utility Functions
f64 rad(const f64 degrees) {return degrees * PI / 180.;}

f64 rand_f64() {return rand() / (RAND_MAX + 1.);}
f64 rand_f64(const f64 min, const f64 max) {return min + (max - min) * rand_f64();}

#include "Ray.hpp"
#include "Vector3.hpp"
#include "Interval.hpp"


#endif