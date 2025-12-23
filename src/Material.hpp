#ifndef _MATERIAL_HPP_
#define _MATERIAL_HPP_


#include "utils.hpp"
#include "HitRegister.hpp"

class HitRegister;

class Material
{
    public:
        virtual ~Material() = default;
        virtual bool scatter(HitRegister& reg, const Ray& R_in, Ray& R_out, vec::Vector3_f64& attenuation) const = 0;
};






class Lambertian : public Material
{
    private:
        vec::Vector3_f64 _albedo;

    public:

        Lambertian(const vec::Vector3_f64& color) : _albedo(color) {}

        bool scatter(HitRegister& reg, const Ray& R_in, Ray& R_out, vec::Vector3_f64& attenuation) const override
        {
            vec::Vector3_f64 scatter_dir = reg.normal + vec::random_unit();

            if (vec::near_zero(scatter_dir))
                scatter_dir = reg.normal;

            R_out.O = reg.P;
            R_out.dir = scatter_dir;
            attenuation = _albedo;
            return 1;
        }
};



class Metal : public Material
{
    private:
        vec::Vector3_f64 _albedo;
        f64 _fuzz;
    
    public:

        Metal(const vec::Vector3_f64& color, const f64 fuzz = 0.) : _albedo(color), _fuzz(fuzz) {}

        bool scatter(HitRegister& reg, const Ray& R_in, Ray& R_out, vec::Vector3_f64& attenuation) const override
        {
            vec::Vector3_f64 reflected = vec::reflect(vec::unit(R_in.dir), reg.normal);
            R_out.O = reg.P;
            R_out.dir = reflected + _fuzz * vec::random_unit();
            attenuation = _albedo;
            return vec::dot(R_out.dir, reg.normal) > 0;
        }
};



class Dielectric : public Material
{
    private:
        f64 _ir; // Index of refraction

        static f64 reflectance(const f64 cosine, const f64 ref_idx) 
        {
            // Use Schlick's approximation for reflectance.
            f64 r0 = (1 - ref_idx) / (1 + ref_idx);
            r0 = r0 * r0;
            return r0 + (1 - r0) * pow((1 - cosine), 5);
        }

    public:
        Dielectric(const f64 index_of_refraction) : _ir(index_of_refraction) {}

        bool scatter(HitRegister& reg, const Ray& R_in, Ray& R_out, vec::Vector3_f64& attenuation) const override
        {
            attenuation = {1., 1., 1.};
            const f64 refraction_ratio = reg.front_face ? (1. / _ir) : _ir;
            const vec::Vector3_f64 unit_dir = vec::unit(R_in.dir);
            // const vec::Vector3_f64 refracted = vec::refract(unit_dir, reg.normal, refraction_ratio);

            const f64 cos_theta = fmin(vec::dot(-unit_dir, reg.normal), 1.);
            const f64 sin_theta = sqrt(1. - cos_theta * cos_theta);

            R_out.O = reg.P;
            
            if (refraction_ratio * sin_theta > 1. || reflectance(cos_theta, refraction_ratio) > rand_f64())
                R_out.dir = vec::reflect(unit_dir, reg.normal);
            
            else
                R_out.dir = vec::refract(unit_dir, reg.normal, refraction_ratio);
            
            // R_out = {reg.P, refracted};
            return 1;
        }

};




#endif