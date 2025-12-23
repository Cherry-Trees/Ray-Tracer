#ifndef _REGISTER_HPP_
#define _REGISTER_HPP_

#include "utils.hpp"

// struct __normal : public vec::Vector3_f64
// {
//     vec::Vector3_f64 normal;
//     vec::Vector3_f64& operator=()
// };

class Material;

struct HitRegister
{
    vec::Vector3_f64 P, normal;
    f64 t;
    bool front_face;
    std::shared_ptr<Material> material;

    /**
     *  Set the surface normal.
     *  NOTE: outward_normal parameter is assumed to be a unit vector.
    */
    void set_normal(const Ray& R, const vec::Vector3_f64& outward_normal)
    {
        front_face = vec::dot(R.dir, outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

#endif