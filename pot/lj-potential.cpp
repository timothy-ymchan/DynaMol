#include "./lj-potential.hpp"

double LennardJones(double sig, double eps, double rij, double& Vij,double& Fij){
    double isr = sig/rij, ir2 = 1.0/(rij*rij), isr2 = isr*isr, isr6 = isr2*isr2*isr2, isr12 = isr6*isr6;

    Vij = 4*eps*(isr12-isr6);
    Fij = 24*eps*ir2*(2*isr12-isr6)*rij;

    return 1.0;
}

double LennardJonesTrim(double sig, double eps, double rij, double cutoff, double& Vij, double& Fij) {
    if(rij > cutoff){
        Vij = Fij = 0.0;
        return 0.0;
    }
    double isr = sig/rij, ir2 = 1.0/(rij*rij), isr2 = isr*isr, isr6 = isr2*isr2*isr2, isr12 = isr6*isr6;
    double isrc = sig/cutoff, isrc2 = isrc*isrc, isrc6 = isrc2*isrc2*isrc2, isrc12 = isrc6*isr6;

    Vij = 4*eps*(isr12+isrc6-isrc12-isr6);
    Fij = 24*eps*ir2*(2*isr12-isr6)*rij;
    return 0.0;
}