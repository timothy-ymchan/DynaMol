#include "../global.hpp"

bool ReflectMin(double& xi, double& vi, double limit);
bool ReflectMax(double& xi, double& vi, double limit);

bool Impose_BCs(vec3& pos, vec3& vel) {
    for(int j=0;j<3;j++){
        ReflectMin(pos[j],vel[j],ximin[j]);
        ReflectMax(pos[j],vel[j],ximax[j]);
    }
    return true;
}

bool ReflectMin(double& xi, double& vi, double limit) {
    if(xi <= limit){
        xi = 2*limit - xi;
        vi = -vi;
    }
    return true;
}

bool ReflectMax(double& xi, double& vi, double limit){
    if(xi >= limit){
        xi = 2*limit - xi;
        vi = -vi;
    }
    return true;
}