#ifndef _DYNAMOL_RAND_H_
#define _DYNAMOL_RAND_H_

/* Utilities for random number generation */
namespace rng{
    void seed(unsigned int s);
    double uniform(); //random number from 0 to 1
    double normal(double mu=0, double sigma=1); //general normal distribution with mu and sigma
}

#endif