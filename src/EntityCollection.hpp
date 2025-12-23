#ifndef _ENTITY_COLLECTION_HPP_
#define _ENTITY_COLLECTION_HPP_

#include "Entity.hpp"

#include <vector>
#include <memory>

class EntityCollection : public Entity
{
    private:
        std::vector<std::shared_ptr<Entity>> _entity_vector;

    public:
        EntityCollection() {}
        EntityCollection(std::shared_ptr<Entity> entity) {add(entity);}

        void clear() {_entity_vector.clear();}
        EntityCollection& add(std::shared_ptr<Entity> entity) {
            _entity_vector.push_back(entity); 
            return *this;
        }

        bool hit(HitRegister& reg, const Ray& R, const Interval_f64& t_interval) const override
        {
            bool hit_anything = 0;
            HitRegister temp_reg;
            f64 closest_so_far = t_interval.max;

            for (auto& entity : _entity_vector)
            {
                if (entity->hit(temp_reg, R, {t_interval.min, closest_so_far}))
                {
                    hit_anything = 1;
                    closest_so_far = temp_reg.t;
                    reg = temp_reg;
                }
            }

            return hit_anything;
        }



};

#endif