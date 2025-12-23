#ifndef _SPHERE_HPP_
#define _SPHERE_HPP_

#include "Entity.hpp"
#include "utils.hpp"
#include "HitRegister.hpp"
#include "Material.hpp"

class Sphere : public Entity
{
    private:
        vec::Vector3_f64 _center;
        f64 _radius;
        std::shared_ptr<Material> _material;


    public:
        Sphere(const vec::Vector3_f64& center, const f64 radius, std::shared_ptr<Material> material) : 
        _center(center), _radius(radius), _material(material) {}



        /**
         *  Solves the equation for a sphere: 
         * 
         *  EQUATION                                                        
         *  --------------------------------------------------------------------------------------------------------------------------
         *  --------------------------------------------------------------------------------------------------------------------------
         * 
         *  ->  x^2 + y^2 + z^2 = r^2                                       ...
         *  ->  (x - C.x)^2 + (y - C.y)^2 + (z - C.z)^2 = r^2               where C ~ sphere center
         *  ->  (P - C) • (P - C) = r^2                                     where P ~ point along the ray 
         *  ->  [P(t) - C] • [P(t) - C] = r^2,                              where t ~ any real valued number
         *  ->  [(A + Bt) - C] • [(A + Bt) - C] = r^2                       where A ~ ray origin, B ~ ray direction, P(t) = A + Bt
         *  ->  [Bt + (A - C)] • [Bt + (A - C)] = r^2                       ...
         *  ->  t^2(B • B) + 2tB • (A - C) + (A - C) • (A - C) - r^2 = 0    ...
         * 
         * 
         *  COEFFICIENTS
         *  --------------------------------------------------------------------------------------------------------------------------
         *  --------------------------------------------------------------------------------------------------------------------------
         * 
         *  ->  a = B • B                                                   ...
         *  ->  b = 2B • (A - C)                                            ...
         *  ->  c = (A - C) • (A - C) - r^2                                 ...
         *  
         *  ->  D = b^2 - 4ac                                               ...
         *  ->  D = [2B • (A - C)]^2 - 4(B • B)[(A - C) • (A - C)]          ...
         *  
         *  --------------------------------------------------------------------------------------------------------------------------
         *  --------------------------------------------------------------------------------------------------------------------------
         * 
        */
        bool hit(HitRegister& reg, const Ray& R, const Interval_f64& t_interval) const override
        {
            /* DEFINITIONS */
            const vec::Vector3_f64 A = R.O;
            const vec::Vector3_f64 B = R.dir;
            const vec::Vector3_f64 C = _center;
            const vec::Vector3_f64 A_C = A - C;
            const f64 r = _radius;

            const f64 a =   vec::dot(B, B);
            const f64 b_2 = vec::dot(B, A_C);
            const f64 c =   vec::dot(A_C, A_C) - r * r;

            const f64 D = b_2 * b_2 - a * c; 
            if (D < 0) return 0;
            const f64 sqrt_D = sqrt(D);

            /* SOLUTION */
            f64 root = (-b_2 - sqrt_D) / a;
            if (!t_interval.contains_excl(root))
            {
                root = (-b_2 + sqrt_D) / a;
                if (!t_interval.contains_excl(root))
                    return 0;
            }
            
            /* UPDATE REGISTER */
            reg.t = root;
            reg.P = R(reg.t);
            reg.set_normal(R, (reg.P - C) / r);
            reg.material = _material;

            return 1;

        }

};

#endif