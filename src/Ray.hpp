#ifndef _RAY_HPP_
#define _RAY_HPP_

#include "Vector3.hpp"

// class Ray
// {
//     private:
//         vec::Vector3_f64 _orig;
//         vec::Vector3_f64 _dir;
    
//     public:
//         Ray() {}
//         Ray(const vec::Vector3_f64& orig, const vec::Vector3_f64& dir) : _orig(orig), _dir(dir) {}

//         vec::Vector3_f64& origin()           {return _orig;}
//         vec::Vector3_f64  origin()    const  {return _orig;}
//         vec::Vector3_f64& direction()        {return _dir;}
//         vec::Vector3_f64  direction() const  {return _dir;}

//         vec::Vector3_f64 operator()(const double t) {return _orig + t * _dir;}       
// };

struct Ray
{
    vec::Vector3_f64 O;
    vec::Vector3_f64 dir;

    vec::Vector3_f64 operator()(const f64 t) const {return O + t * dir;}       
};

#endif