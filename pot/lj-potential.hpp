#pragma once
#include "../math/vec3.hpp"


double LennardJones(double sig, double eps, double rij, double& Vij,double& Fij);

double LennardJonesTrim(double sig, double eps, double rij, double cutoff, double& Vij, double& Fij);