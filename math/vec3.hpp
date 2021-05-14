#ifndef _DYNAMOL_VEC3_H_
#define _DYNAMOL_VEC3_H_

#include <cmath>
#include <array>

/* Vector class */
class vec3{
    private:
    std::array<double,3> val;

    public:
    /* Constructor */
    vec3();
    vec3(double x1, double x2, double x3);

    /* Access */
    double &operator[](int i) { return val[i]; };
    double operator[](int i) const {return val[i];};

    /* Other operation*/
    double fill(double num);

    /* Operator overloads */
    friend vec3 operator+(vec3 const &v1, vec3 const &v2);
    friend vec3 operator+(double const& c, vec3 const& v1);
    friend vec3 operator+(vec3 const& v1, double const& c);
    friend vec3 operator-(vec3 const& v1, vec3 const& v2);
    friend vec3 operator-(vec3 const& v1, double const& c);
    friend vec3 operator*(double const &k, vec3 const &v1);
    friend vec3 operator*(vec3 const &v1, double const &k);
    friend vec3 operator/(vec3 const &v1,double const &k);
    

};

namespace vec
{
    double dot(vec3 v1, vec3 v2); //dot product
    vec3 cross(vec3 v1, vec3 v2); //cross product
    double norm(vec3 v);          //2-norm
};
#endif