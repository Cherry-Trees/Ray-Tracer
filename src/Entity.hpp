#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

#include "utils.hpp"
#include "HitRegister.hpp"

class Entity
{
    private:
    
    public:
        virtual ~Entity() = default;
        virtual bool hit(HitRegister&, const Ray&, const Interval_f64&) const = 0;
};


#endif