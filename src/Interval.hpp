#ifndef _INTERVAL_HPP_
#define _INTERVAL_HPP_

#include "utils.hpp"

template<typename T> struct Interval
{
    T min, max;

    Interval() : min(+INF), max(-INF) {}
    Interval(const T min, const T max) : min(min), max(max) {}

    bool contains_incl(const T t) const {return t >= min && t <= max;}
    bool contains_excl(const T t) const {return t > min && t < max;}

    f64 clamp(const f64 x) const 
    {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }

    // static const Interval empty{+INF, -INF};
    // static const Interval all{-INF, +INF};
};

typedef Interval<int> Interval_i32;
typedef Interval<float> Interval_f32;
typedef Interval<double> Interval_f64;

#endif