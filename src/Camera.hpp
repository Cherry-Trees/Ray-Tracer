#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_


#include "utils.hpp"

#include "Color.hpp"
#include "Entity.hpp"
#include "EntityCollection.hpp"
#include "Sphere.hpp"
#include "Material.hpp"

class Camera {
    private:
        u32                 image_height;
        vec::Vector3_f64    center;
        vec::Vector3_f64    upper_left_pixel_loc;
        vec::Vector3_f64    pixel_du;
        vec::Vector3_f64    pixel_dv;
        vec::Vector3_f64    u, v, w;
        vec::Vector3_f64    defocus_disk_u, defocus_disk_v;

        void _init() 
        {
            // Image
            // const f64 aspect_ratio = 16. / 9.;
            // const u32 image_width = 1280u;
            image_height = std::max(static_cast<u32>(image_width / aspect_ratio), 1u);

            // Viewport and camera
            // const f64 focal_length = vec::norm(look_from - look_at);
            center = look_from;


            const f64 vfov_rad = rad(vfov);
            const f64 h = tan(vfov_rad / 2.);

            const f64 viewport_height = 2. * h * focus_dist;
            const f64 viewport_width = viewport_height * (static_cast<f64>(image_width) / image_height);

            w = vec::unit(look_from - look_at);
            u = vec::unit(vec::cross(vup, w));
            v = vec::cross(w, u);


            

            // Vectors running along the horizontal and vertical of the viewport
            const vec::Vector3_f64 viewport_u = u * viewport_width;
            const vec::Vector3_f64 viewport_v = v * -viewport_height;

            // U and V step size
            pixel_du = viewport_u / image_width;
            pixel_dv = viewport_v / image_height;

            // Starting pixel
            const vec::Vector3_f64 viewport_upper_left = center - focus_dist * w - viewport_u / 2 - viewport_v / 2;
            upper_left_pixel_loc = viewport_upper_left + pixel_du / 2 + pixel_dv / 2;

            const f64 defocus_radius = focus_dist * tan(rad(defocus_angle / 2.));
            defocus_disk_u = u * defocus_radius;
            defocus_disk_v = v * defocus_radius;
        }

        vec::Vector3_f64 sample_pixel() const
        {
            f64 px = rand_f64() - 0.5;
            f64 py = rand_f64() - 0.5;

            return (px * pixel_du) + (py * pixel_dv);
        }

        vec::Vector3_f64 _ray_color(const Ray& R, const Entity& world, const u32 current_depth) const 
        {
            if (!current_depth) return {0., 0., 0.};
            HitRegister reg;

            
            if (world.hit(reg, R, {0.001, INF})) // <- t_min = 0.001 fixes shadow acne.
            {
                Ray scattered;
                vec::Vector3_f64 attenuation;
                if (reg.material->scatter(reg, R, scattered, attenuation))
                    return attenuation * _ray_color(scattered, world, current_depth - 1);
                
                return {0., 0., 0.};
                // vec::Vector3_f64 random_dir = reg.normal + vec::random_unit(); // Lambertian reflectance
                // vec::Vector3_f64 random_dir = vec::random_on_hemisphere(reg.normal);
                // return 0.2 * _ray_color({reg.P, random_dir}, world, current_depth - 1);
                // return 0.5 * (reg.normal + vec::Vector3_f64(1,1,1));
            }
            

            f64 a = 0.5 * (vec::unit(R.dir).y + 1.);
            return (1. - a) * vec::Vector3_f64(1., 1., 1.) + a * vec::Vector3_f64(0.5, 0.7, 1.);
        }

        Ray _get_ray(const u32 i, const u32 j) const
        {
            const vec::Vector3_f64 pixel_center = upper_left_pixel_loc + (pixel_du * j) + (pixel_dv * i);
            const vec::Vector3_f64 pixel_center_sample = pixel_center + sample_pixel();
            const vec::Vector3_f64 ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();//center;
            const vec::Vector3_f64 ray_direction = pixel_center_sample - ray_origin;
            return {ray_origin, ray_direction};
        }

        vec::Vector3_f64 defocus_disk_sample() const {
            // Returns a random point in the camera defocus disk.
            auto p = vec::random_in_unit_disk();
            return center + (p.x * defocus_disk_u) + (p.y * defocus_disk_v);
        }


    public:
        u32 image_width             = 400u;
        f64 aspect_ratio            = 1.;
        u32 samples_per_pixel       = 10u;
        u32 max_depth               = 10u;
        f64 vfov                    = 90.;
        vec::Vector3_f64 look_from  = {0., 0., 0.};
        vec::Vector3_f64 look_at    = {0., 0., -1.};
        vec::Vector3_f64 vup        = {0., 1., 0.};

        f64 defocus_angle           = 0.;
        f64 focus_dist              = 10.;

    void render(const Entity& world) 
    {
        _init();
        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
        for (u32 i = 0; i < image_height; i++)
        {
            std::clog << "\rScanlines remaining: " << (image_height - i) << ' ' << std::flush;
            for (u32 j = 0; j < image_width; j++)
            {
                vec::Vector3_f64 pixel_color{0., 0., 0.};
                for (u32 sample = 0; sample < samples_per_pixel; sample++)
                {
                    Ray R = _get_ray(i, j);
                    pixel_color += _ray_color(R, world, max_depth);
                    
                }
                // const vec::Vector3_f64 pixel_center = upper_left_pixel_loc + (pixel_du * j) + (pixel_dv * i);
                // const vec::Vector3_f64 ray_direction = pixel_center - center;
                // const Ray R{center, ray_direction};
                // const vec::Vector3_f64 pixel_color = _ray_color(R, world);

                write_color(pixel_color, samples_per_pixel);
            }
        }
        std::clog << "\rDone.                 \n";
    }

  
};

#endif