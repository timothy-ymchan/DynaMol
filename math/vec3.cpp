#include "vec3.hpp"

double vec::dot(vec3 v1, vec3 v2) { 
    return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
};

vec3 vec::cross(vec3 v1, vec3 v2) { 
    return vec3(
        v1[1]*v2[2]-v1[2]*v2[1],
        v1[2]*v2[0]-v1[0]*v2[2],
        v1[0]*v2[1]-v1[1]*v2[0]
    );
};

double vec::norm(vec3 v) {
    return sqrt(vec::dot(v,v));
}
vec3::vec3(){
    val[0] = val[1] = val[2] = 0.0;
}

vec3::vec3(double x1, double x2, double x3){
    val[0] = x1; val[1] = x2; val[2] = x3;
}

double vec3::fill(double num){
    return val[0] = val[1] = val[2] = num;
}

vec3 operator+(vec3 const &v1, vec3 const &v2) {
    vec3 v3;
    for(int i=0;i<3;i++){
        v3[i] = v1[i] + v2[i];
    }
    return v3;
}

vec3 operator+(double const& c, vec3 const& v1){
    vec3 v2;
    for(int i =0; i < 3;i++){
        v2[i] = v1[i] + c;
    }
    return v2;
}

vec3 operator+(vec3 const& v1,double const& c){
    return c + v1;
}

vec3 operator-(vec3 const& v1, vec3 const& v2) {
    vec3 v3;
    for(int i=0;i<3;i++){
        v3[i] = v1[i] - v2[i];
    }
    return v3;
}

vec3 operator-(vec3 const& v1, double const& c){
    return -c + v1;
}

vec3 operator*(double const &k, vec3 const &v1){
    vec3 v2;
    for(int i =0; i < 3;i++){
        v2[i] = k*v1[i];
    }
    return v2;
}

vec3 operator*(vec3 const &v1,double const &k){
    return k*v1;
}


vec3 operator/(vec3 const &v1,double const &k) {
    return (1.0/k)*v1;
}
