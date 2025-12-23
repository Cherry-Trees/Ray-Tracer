#ifndef _VECTOR_3_HPP_
#define _VECTOR_3_HPP_

#include <cmath>
#include "utils.hpp"


typedef char            i8;
typedef unsigned char   u8;
typedef short           i16;
typedef unsigned short  u16;
typedef int             i32;
typedef unsigned int    u32;
typedef float           f32;
typedef double          f64;

namespace vec
{

    template<typename T> struct Vector3
    {
        T x, y, z;

        Vector3() {}
        Vector3(const T& x, const T& y, const T& z) : x(x), y(y), z(z) {}

        Vector3<T> operator+(const Vector3<T>& _Vec) const 
        {
            return {x + _Vec.x, y + _Vec.y, z + _Vec.z};
        }

        Vector3<T> operator-(const Vector3<T>& _Vec) const 
        {
            return {x - _Vec.x, y - _Vec.y, z - _Vec.z};
        }

        Vector3<T> operator-() const
        {
            return {-x, -y, -z};
        }

        Vector3<T> operator*(const T& _Scalar) const 
        {
            return {x * _Scalar, y * _Scalar, z * _Scalar};
        }

        Vector3<T> operator/(const T& _Scalar) const 
        {
            return {x / _Scalar, y / _Scalar, z / _Scalar};
        }

        Vector3<T>& operator+=(const Vector3<T>& _Vec) 
        {
            x += _Vec.x;
            y += _Vec.y;
            z += _Vec.z;
            return *this;
        }

        Vector3<T>& operator-=(const Vector3<T>* _Vec) 
        {
            x -= _Vec.x;
            y -= _Vec.y;
            z -= _Vec.z;
            return *this;
        }

        Vector3<T>& operator*=(const T& _Scalar) 
        {
            x *= _Scalar;
            y *= _Scalar;
            z *= _Scalar;
            return *this;
        }

        Vector3<T>& operator/=(const T& _Scalar) 
        {
            x /= _Scalar;
            y /= _Scalar;
            z /= _Scalar;
            return *this;
        }

        Vector3<T>& operator=(const Vector3<T>& _Vec)
        {
            x = _Vec.x;
            y = _Vec.y;
            z = _Vec.z;
            return *this;
        }


        Vector3<T> operator*(const Vector3<T>& _Vec)
        {
            return {
                x * _Vec.x,
                y * _Vec.y,
                z * _Vec.z
            };
        }
    };

    typedef Vector3<i32> Vector3_i32;
    typedef Vector3<u32> Vector3_u32;
    typedef Vector3<f32> Vector3_f32;
    typedef Vector3<f64> Vector3_f64;

    Vector3_f64 operator""_X(const long double x) {return {static_cast<f64>(x), 0, 0};}
    Vector3_f64 operator""_Y(const long double y) {return {0, static_cast<f64>(y), 0};}
    Vector3_f64 operator""_Z(const long double z) {return {0, 0, static_cast<f64>(z)};}

    template<typename T> Vector3<T> X(const T& x) {return {x, 0, 0};}
    template<typename T> Vector3<T> Y(const T& y) {return {0, y, 0};}
    template<typename T> Vector3<T> Z(const T& z) {return {0, 0, z};}

    template<typename T> Vector3<T> Zero() {return {0, 0, 0};}
    Vector3_f64 Random() {return {rand_f64(), rand_f64(), rand_f64()};}
    Vector3_f64 Random(const f64 min, const f64 max) {return {rand_f64(min, max), rand_f64(min, max), rand_f64(min, max)};}

    template<typename T> Vector3<T> operator*(const T& _Scalar, const Vector3<T>& _Vec) 
    {
        return {
            _Vec.x * _Scalar, 
            _Vec.y * _Scalar, 
            _Vec.z * _Scalar
        };
    }

    template<typename T> Vector3<T> operator/(const T& _Scalar, const Vector3<T>& _Vec) 
    {
        return {
            _Scalar / _Vec.x, 
            _Scalar / _Vec.y, 
            _Scalar / _Vec.z
        };
    }

    template<typename T> T dot(const Vector3<T>& _Vec_A, const Vector3<T>& _Vec_B) 
    {
        return _Vec_A.x * _Vec_B.x + 
            _Vec_A.y * _Vec_B.y + 
            _Vec_A.z * _Vec_B.z;
    }

    template<typename T> Vector3<T> cross(const Vector3<T>& _Vec_A, const Vector3<T>& _Vec_B) 
    {
        return {
            _Vec_A.y * _Vec_B.z - _Vec_A.z * _Vec_B.y,
            _Vec_A.z * _Vec_B.x - _Vec_A.x * _Vec_B.z,
            _Vec_A.x * _Vec_B.y - _Vec_A.y * _Vec_B.x
        };
    }

    template<typename T> T norm(const Vector3<T>& _Vec) 
    {
        return std::sqrt(
            _Vec.x * _Vec.x +
            _Vec.y * _Vec.y +
            _Vec.z * _Vec.z
        );
    }

    template<typename T> T norm(const Vector3<T>& _Vec_A, const Vector3<T>& _Vec_B) 
    {
        return sqrt(
            (_Vec_A.x - _Vec_B.x) * (_Vec_A.x - _Vec_B.x) +
            (_Vec_A.y - _Vec_B.y) * (_Vec_A.y - _Vec_B.y) +
            (_Vec_A.z - _Vec_B.z) * (_Vec_A.z - _Vec_B.z)
        );
    }

    template<typename T> T norm_square(const Vector3<T>& _Vec) 
    {
        return (
            _Vec.x * _Vec.x +
            _Vec.y * _Vec.y +
            _Vec.z * _Vec.z
        );
    }

    template<typename T> T norm_square(const Vector3<T>& _Vec_A, const Vector3<T>& _Vec_B) 
    {
        return (
            (_Vec_A.x - _Vec_B.x) * (_Vec_A.x - _Vec_B.x) +
            (_Vec_A.y - _Vec_B.y) * (_Vec_A.y - _Vec_B.y) +
            (_Vec_A.z - _Vec_B.z) * (_Vec_A.z - _Vec_B.z)
        );
    }

    template<typename T> Vector3<T> unit(const Vector3<T>& _Vec) 
    {
        return _Vec / norm(_Vec);
    }

    Vector3_f64 random_in_unit_sphere()
    {
        while (1)
        {
            Vector3_f64 v = Random(-1., 1.);
            if (norm_square(v) < 1)
                return v;
        }
    }

    Vector3_f64 random_unit()
    {
        return unit(random_in_unit_sphere());
    }

    Vector3_f64 random_on_hemisphere(const Vector3_f64& normal)
    {
        Vector3_f64 on_sphere = random_unit();

        if (dot(on_sphere, normal) > 0.)    return on_sphere;
        else                                return -on_sphere;
    }

    bool near_zero(const Vector3_f64& _Vec)
    {
        f64 s = 1e-8;
        return (fabs(_Vec.x) < s) && (fabs(_Vec.y) < s) && (fabs(_Vec.z) < s);
    }

    Vector3_f64 reflect(const Vector3_f64& v, const Vector3_f64& n)
    {
        return v - 2. * dot(v, n) * n;
    }

    Vector3_f64 refract(const Vector3_f64& v, const Vector3_f64& n, const f64 etai_over_etat)
    {
        const f64 cos_theta = fmin(dot(-v, n), 1.);
        const Vector3_f64 R_perpendicular = etai_over_etat * (v + cos_theta * n);
        const Vector3_f64 R_parallel = -sqrt(fabs(1. - norm_square(R_perpendicular))) * n;
        return R_perpendicular + R_parallel;
    }

    Vector3_f64 random_in_unit_disk() {
        while (true) {
            Vector3_f64 p = Vector3_f64(rand_f64(-1.,1.), rand_f64(-1.,1.), 0);
            if (norm_square(p) < 1)
                return p;
        }
}

}

#endif