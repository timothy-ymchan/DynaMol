#include "rand.hpp"
#include "consts.hpp"
#include <cstdlib>
#include <cmath>

void rng::seed(unsigned int s){
    srand(s);
}

double rng::uniform(){
    return ((double)rand())/RAND_MAX;   
}


double rng::normal(double mu, double sigma) {
    double x1 = rng::uniform(), x2 = rng::uniform();
    return sqrt(-2*log(x1))*cos(2*PI*x2)*sigma + mu; /* Box Muller transform */
}