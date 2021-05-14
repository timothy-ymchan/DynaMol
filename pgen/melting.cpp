#include "../global.hpp"
#include "math/rand.hpp"

#define PTYPE_AR 0
#define PTYPE_XE 1

double k, T, m_Ar, m_Xe;
double sig_ArAr, sig_ArXe, sig_XeXe;
double eps_ArAr, eps_ArXe, eps_XeXe;

const char* pname[] = {"Ar","Xe"};

void ReadConstants();

vec3 MaxwellBoltz(double mass);
void SetSigma(int t1, int t2, double sig) {SIGMA[t1][t2]=SIGMA[t2][t1] = sig;};
void SetEpsilon(int t1, int t2, double eps) {EPSILON[t1][t2]=EPSILON[t2][t1] = eps;};

void WriteTraj(FILE* fp);
void WriteTemp(FILE* fp);
void WriteEnergy(FILE* fp);
void WriteState(FILE* fp);

bool Problem_Init() {

    printf("Diffusion of Xenon in Argon liquid \n");

    rng::seed(100);

    /* Read in constants to make code nicer */
    ReadConstants();

    /* Initialize lookup table of interactions */
    SetSigma(PTYPE_AR,PTYPE_AR,sig_ArAr);
    SetSigma(PTYPE_AR,PTYPE_XE,sig_ArXe);
    SetSigma(PTYPE_XE,PTYPE_XE,sig_XeXe);
    SetEpsilon(PTYPE_AR,PTYPE_AR,eps_ArAr);
    SetEpsilon(PTYPE_AR,PTYPE_XE,eps_ArXe);
    SetEpsilon(PTYPE_XE,PTYPE_XE,eps_XeXe);

    /* Initialize Sweep-Prune Optimization */
    SP_CUTOFF = 5*(sig_XeXe);

    /* Initialize position and velocities */
    int N = ceil(pow(mol_no,1.0/3.0)); //Grid dimension (cube root of N)
    
    double  dx1 = (x1max-x1min)/(N+1), //Cell seperations
            dx2 = (x2max-x2min)/(N+1),
            dx3 = (x3max-x3min)/(N+1);

    vec3 cm_corr = vec3(0,0,0);
    for(int i=0;i<mol_no;i++){

        /* Mass and type of atoms */
        MASS[i] = (i == mol_no/2)? m_Ar : m_Ar;
        TYPE[i] = (i == mol_no/2)? PTYPE_AR : PTYPE_AR;

        /* Grid position */
        double  x1 = x1min + dx1 + (i%N)*dx1,  
                x2 = x2min + dx2 + ((i/N)%N)*dx2,
                x3 = x3min + dx3 + (((i/N)/N)%N)*dx3; 
        POS[i] = vec3(x1,x2,x3);
        
        /* Set velocity */
        VEL[i] = MaxwellBoltz(MASS[i]);
        cm_corr = cm_corr + MASS[i]*VEL[i];

        /* Set acceleration */
        ACL[i] = vec3(0,0,0);
    }

    /* Center of mass correction */
    cm_corr = cm_corr*(1.0/mol_no);
    for(int i=0;i<mol_no;i++){
        VEL[i] = VEL[i] - (1.0/MASS[i])*cm_corr;
    }

    /* Register output writer */ 
    dmoutput.RegisterWriter("./traj.xyz",0.5,WriteTraj);
    dmoutput.RegisterWriter("./temp.dat",5.0,WriteTemp);
    dmoutput.RegisterWriter("./energy.dat",5.0,WriteEnergy);
    dmoutput.RegisterWriter("./state.dat",100,WriteState);
    return true;
}

bool After_Step() {
    return true;
}


void WriteTraj(FILE* fp) {
    fprintf(fp,"%d\nEMPTY LINE\n",mol_no);
    for(int i=0;i<mol_no;i++){
        fprintf(fp,"%s\t%.20lf\t%.20lf\t%.20lf\n",pname[TYPE[i]],POS[i][0],POS[i][1],POS[i][2]);
    }
}

void WriteTemp(FILE* fp) {
    fprintf(fp,"%lf\t%lf\n",t_now,TEMP);
}

void WriteEnergy(FILE* fp) {
    double KE = AVG_EN[SYS_KE].sum()/AVG_EN[SYS_KE].size();
    double PE = AVG_EN[SYS_PE].sum()/AVG_EN[SYS_PE].size();
    fprintf(fp,"%lf\t%lf\t%lf\t%lf\n",t_now,KE,PE,KE+PE);
}

void WriteState(FILE* fp) {
    printf("%lf\n",t_now);
    for(int i=0;i<mol_no;i++){
        fprintf(fp,"%s\t%.20lf\t%.20lf\t%.20lf\t%.20lf\t%.20lf\t%.20lf\n",pname[TYPE[i]],POS[i][0],POS[i][1],POS[i][2],VEL[i][0],VEL[i][1],VEL[i][2]);
    }
    printf("\n");
}

void ReadConstants() {
    k = dminput.GetReal("kb");
    T = dminput.GetReal("T");
    m_Ar = dminput.GetReal("m_Ar")*dminput.GetReal("m0");
    m_Xe = dminput.GetReal("m_Xe")*dminput.GetReal("m0");

    sig_ArAr = dminput.GetReal("sig_ArAr");
    sig_ArXe = dminput.GetReal("sig_ArXe");
    sig_XeXe = dminput.GetReal("sig_XeXe");

    eps_ArAr = dminput.GetReal("eps_ArAr");
    eps_ArXe = dminput.GetReal("eps_ArXe");
    eps_XeXe = dminput.GetReal("eps_XeXe");
}

vec3 MaxwellBoltz(double mass) {
    double v0 = sqrt(dminput.GetReal("kb")*dminput.GetReal("T")/mass);
    double  n1 = rng::normal(), 
                n2 = rng::normal(), 
                n3 = rng::normal();
    return v0*vec3(n1,n2,n3);
}