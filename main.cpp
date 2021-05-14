#include <stdio.h>
#include <stdlib.h>
#include "global.hpp"
#include "pot/lj-potential.hpp"

/* Global variables */
std::string INPUT_FILE_PATH;
DM_Input dminput;

OutputWriterList dmoutput;

/* Basic parameters */
double t_now, t_lim, delta_t;
int mol_no;
double ximin[3], ximax[3];
double x1min, x1max, x2min,x2max, x3min, x3max; //box boundaries

/* Particle states */
std::vector<vec3> POS;
std::vector<vec3> VEL;
std::vector<vec3> ACL;
std::vector<int> TYPE;
std::vector<double> MASS;

double SIGMA[10][10];
double EPSILON[10][10];


/* Energy and Temperature */
double EN[2];
double TEMP;
Queue AVG_EN[2];


/* Berendsen thermostat */
bool BEN_ENABLE;
double BEN_TEMP;
double BEN_TAU; 

int main(int argc, char* argv[]) {
    bool success = true;
    success &= Core_Init(argc,argv);
    printf("Success: %d\n",(success==true)?1:0);
    success &= Problem_Init();
    printf("Success: %d\n",(success==true)?1:0);

    /* Main loop */
    while(success && t_now < t_lim) {

        success &= Step_Time();
        success &= After_Step();
        dmoutput.WriteAll(t_now); //Write output files

        t_now += delta_t;
    }
    printf("END~ %f %d\n",t_now,(success==true)?1:0);
}

bool Step_Time() {
    /* Verlet method */
    /* Update position (stage 1) */
    for(int i=0; i<mol_no; i++) {
        POS[i] = POS[i] + (VEL[i] + 0.5*ACL[i]*delta_t)*delta_t;
    
        /* Impose boundary conditions */
        Impose_BCs(POS[i],VEL[i]);

        VEL[i] = VEL[i] + 0.5*ACL[i]*delta_t;
    }
    
    /* Calculate new acceleration (Step 2) */
    EN[SYS_PE] = 0.0;
    for(int k=0;k<mol_no;k++)
        ACL[k][0] = ACL[k][1] = ACL[k][2] = 0; // Reset acceleration
    
    int count = 0;
    if(SP_ENABLE){
        SweepPrune_Sort();
        SweepPrune_CheckIntersect();

        /* Sweep and Prune algorithm (faster) */
        for(auto pairs:SP_CHECKPAIRS) {
            int i = std::get<0>(pairs);
            int j = std::get<1>(pairs);

            double Vij, Fij;
            vec3 rij = POS[i] - POS[j];
            double r = vec::norm(rij);
            vec3 rhat = rij/r;
            
            int ti = TYPE[i], tj = TYPE[j];
            LennardJonesTrim(SIGMA[ti][tj],EPSILON[ti][tj],r,3*SIGMA[ti][tj],Vij,Fij);

            EN[SYS_PE] += Vij;
            ACL[i] = ACL[i] + Fij*rhat/MASS[i];
            ACL[j] = ACL[j] - Fij*rhat/MASS[j];
        }
    } else {
        /* Pairwise algorithm (slow) */
        for(int i=0;i<mol_no-1;i++){
            for(int j=i+1;j<mol_no;j++){

                /* Calculate pair-wise force */
                double Vij, Fij;
                vec3 rij = POS[i] - POS[j];
                double r = vec::norm(rij);
                vec3 rhat = rij/r;
                
                int ti = TYPE[i], tj = TYPE[j]; 
                LennardJonesTrim(SIGMA[ti][tj],EPSILON[ti][tj],r,3*SIGMA[ti][tj],Vij,Fij);

                EN[SYS_PE] += Vij;
                ACL[i] = ACL[i] + Fij*rhat/MASS[i];
                ACL[j] = ACL[j] - Fij*rhat/MASS[j];
            }
        }
    }
    


    /* Update velocities again & impose boundary conditions (Step 3)*/
    EN[SYS_KE] = 0.0;
    for(int i=0;i<mol_no;i++){
        VEL[i] = VEL[i] + 0.5*ACL[i]*delta_t;

        EN[SYS_KE] += 0.5*MASS[i]*vec::dot(VEL[i],VEL[i]);
    }

    /* Moving average */
    AVG_EN[SYS_KE].fenqueue(EN[SYS_KE]);
    AVG_EN[SYS_PE].fenqueue(EN[SYS_PE]);
    TEMP = ((2.0/(3.0*dminput.GetReal("kb")))*AVG_EN[SYS_KE].sum()/AVG_EN[SYS_KE].size())/mol_no;

    /* Berendsen Thermostat */
    if(BEN_ENABLE) {
        double BEN_CORR = sqrt(1+(delta_t/BEN_TAU)*(BEN_TEMP/TEMP - 1.0));
        for(int i=0;i<mol_no;i++){
            VEL[i] = BEN_CORR*VEL[i];
        }
    }
    

    return true;
}

bool Core_Init(int argc, char* argv[]) {

    /* Read arguments */
    if(argc != 2){
        printf("Error: Invalid arguments\n");
        return false;
    }

    /* Open Input file */
    INPUT_FILE_PATH = std::string(argv[1]);
    if(!dminput.open(INPUT_FILE_PATH)){
        return false;
    }

    /* Initialize basic parameters */
    t_now = 0;
    t_lim = dminput.GetReal("t_lim");       //simulation limit
    delta_t = dminput.GetReal("dt");        //dt
    mol_no = dminput.GetInt("N");           //no of molecules

    /* Get box boundaries */
    x1min = ximin[0] = dminput.GetReal("x1min");
    x1max = ximax[0] = dminput.GetReal("x1max");
    x2min = ximin[1] = dminput.GetReal("x2min");
    x2max = ximax[1] = dminput.GetReal("x2max");
    x3min = ximin[2] = dminput.GetReal("x3min");
    x3max = ximax[2] = dminput.GetReal("x3max");

    /* Create particle array */
    POS = std::vector<vec3>(mol_no);
    VEL = std::vector<vec3>(mol_no);
    ACL = std::vector<vec3>(mol_no);
    MASS = std::vector<double>(mol_no);
    TYPE = std::vector<int>(mol_no);

    /* Initialize output writer list */
    dmoutput = OutputWriterList();


    /* Sweep-Prune optimization */
    SP_ENABLE = dminput.GetOrSetBool("sp_enable",false);
    if(SP_ENABLE) SweepPrune_Init();

    /* Initialize moving average */
    AVG_EN[SYS_KE] = Queue(dminput.GetInt("moving_average_frames"));
    AVG_EN[SYS_PE] = Queue(dminput.GetInt("moving_average_frames"));

    /* Initialize thermostat */
    BEN_ENABLE = dminput.GetOrSetBool("thermostat_enable",false);
    if(BEN_ENABLE){
        BEN_TEMP = dminput.GetReal("thermostat_temp");
        BEN_TAU  = dminput.GetReal("thermostat_tau");
    }

    return true;
}