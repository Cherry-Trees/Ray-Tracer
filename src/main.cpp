#include "utils.hpp"
#include "Color.hpp"
#include "Ray.hpp"

#include "Camera.hpp"
#include "Entity.hpp"
#include "EntityCollection.hpp"
#include "Sphere.hpp"

#include <iostream>



    /********************     **********     ********************/
    /********************     **********     ********************/



using namespace vec;


typedef Vector3_f64 Vec3_f64;


// Vec3_f64 ray_color(const Ray& R, const Entity& world)
// {
//     HitRegister reg;
//     if (world.hit(reg, R, {0, INF})) {
//         return 0.5 * (reg.normal + Vec3_f64(1,1,1));
//     }

//     f64 a = 0.5 * (unit(R.dir).y + 1.);
//     return (1. - a) * Vec3_f64(1., 1., 1.) + a * Vec3_f64(0.5, 0.7, 1.);
// }

int main(i32 argc, i8** argv)
{

    // // Image
    // const f64 aspect_ratio = 16. / 9.;
    // const u32 image_width = 1280u;
    // const u32 image_height = std::max(static_cast<u32>(image_width / aspect_ratio), 1u);

    // // Entities
    // EntityCollection world;
    // world.add(std::make_shared<Sphere>(Vec3_f64(0, 0, -1), 0.5));
    // world.add(std::make_shared<Sphere>(Vec3_f64(0,-100.5,-1), 100));

    // // Viewport and camera
    // const f64 focal_length = 1.;
    // const f64 viewport_height = 2.;
    // const f64 viewport_width = viewport_height * (static_cast<f64>(image_width) / image_height);
    // const Vec3_f64 camera_center = Zero<f64>();

    // // Vectors running along the horizontal and vertical of the viewport
    // const Vec3_f64 viewport_u = X(viewport_width);
    // const Vec3_f64 viewport_v = Y(-viewport_height);

    // // U and V step size
    // const Vec3_f64 viewport_du = viewport_u / image_width;
    // const Vec3_f64 viewport_dv = viewport_v / image_height;

    // // Starting pixel
    // const Vec3_f64 viewport_upper_left = camera_center - Z(focal_length) - viewport_u / 2 - viewport_v / 2;
    // const Vec3_f64 upper_left_pixel_loc = viewport_upper_left + viewport_du / 2 + viewport_dv / 2;


    // std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    // for (u32 i = 0; i < image_height; i++)
    // {
    //     for (u32 j = 0; j < image_width; j++)
    //     {
    //         const Vec3_f64 pixel_center = upper_left_pixel_loc + (viewport_du * j) + (viewport_dv * i);
    //         const Vec3_f64 ray_direction = pixel_center - camera_center;
    //         const Ray R{camera_center, ray_direction};
    //         const Vec3_f64 pixel_color = ray_color(R, world);

    //         std::cout << pixel_color;
    //     }
    // }

    EntityCollection world;

    // std::shared_ptr<Material> mat1 = std::make_shared<Material>() 

    // world.add(std::make_shared<Sphere>(Vec3_f64(-.5, 0., -1.), 0.5));
    // world.add(std::make_shared<Sphere>(Vec3_f64(.5, 0., -1.), 0.5));
    // world.add(std::make_shared<Sphere>(Vec3_f64(0,-100.5,-1), 100));

    auto material_ground = std::make_shared<Lambertian>(vec::Vector3_f64(0.2, 0.3, 0.4));
    auto material_center = std::make_shared<Lambertian>(vec::Vector3_f64(0.7, 0.3, 0.3));
    auto material_left   = std::make_shared<Metal>(vec::Vector3_f64(0.8, 0.8, 0.8), 0.02);
    auto material_right  = std::make_shared<Metal>(vec::Vector3_f64(0.8, 0.6, 0.2), .8);

    world.add(std::make_shared<Sphere>(vec::Vector3_f64( 0.0, -100.5, -1.0), 100.0, material_ground));
    // world.add(std::make_shared<Sphere>(vec::Vector3_f64( 0.0,    0.0, -1.0),   0.5, material_left));
    world.add(std::make_shared<Sphere>(vec::Vector3_f64(-.5,    0.0, -1.0),   0.5, material_left));
    world.add(std::make_shared<Sphere>(vec::Vector3_f64( 1.0,    1., -2.0),   1.5, material_right));
    world.add(std::make_shared<Sphere>(vec::Vector3_f64(-0.1,    -0.35, -0.575), 0.15, material_left));

    // auto material_ground = std::make_shared<Lambertian>(vec::Vector3_f64(0.4, 0.4, 0.45));
    // auto material_center = std::make_shared<Lambertian>(vec::Vector3_f64(0.1, 0.2, 0.5));
    // auto material_left   = std::make_shared<Dielectric>(1.5);
    // auto material_right  = std::make_shared<Metal>(vec::Vector3_f64(0.8, 0.8, 0.8), 0.01);

    // world.add(std::make_shared<Sphere>(vec::Vector3_f64( 0.0, -100.5, -1.0), 100.0, material_ground));
    // world.add(std::make_shared<Sphere>(vec::Vector3_f64( 0.5,    2.0, -6.0),   2.5, material_right));

    // world.add(std::make_shared<Sphere>(vec::Vector3_f64(-0.5,    0.0, -1.0),   0.5, material_left));
    // world.add(std::make_shared<Sphere>(vec::Vector3_f64(-0.5,    0.0, -1.0),  -0.4, material_left));
    // // world.add(std::make_shared<Sphere>(vec::Vector3_f64( 1.0,    0.0, -1.0),   0.5, material_right));

    Camera camera;
    camera.aspect_ratio         = 16. / 9.;
    camera.image_width          = 400u;
    camera.samples_per_pixel    = 20u;
    camera.max_depth            = 50u;

    camera.vfov                 = 45.;
    camera.look_from            = {-0., 1., 0.};
    camera.look_at              = {0., -0., -1.}; 
    camera.vup                  = {0., 1., 0.};

    camera.defocus_angle = 0;
    camera.focus_dist    = 3.;
    
    camera.render(world);





    return 0;
}
