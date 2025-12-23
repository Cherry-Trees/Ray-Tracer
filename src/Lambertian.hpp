#ifndef _LAMBERTIAN_HPP_
#define _LAMBERTIAN_HPP_

#include "Material.hpp"
#include "HitRegister.hpp"

class Lambertian : public Material
{
    private:
        vec::Vector3_f64 _albedo;

    public:

        Lambertian(const vec::Vector3_f64& color) : _albedo(color) {}

        bool scatter(HitRegister& reg, const Ray& R_in, Ray& R_out, vec::Vector3_f64& attenuation) const override
        {
            vec::Vector3_f64 scatter_dir = reg.normal + vec::random_unit();
            R_out.O = reg.P;
            R_out.dir = scatter_dir;
            attenuation = _albedo;
            return 1;
        }
};


#endif