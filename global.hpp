#pragma once
#include <vector>
#include <string>
#include "math/vec3.hpp"
#include "input/inputreader/input_reader.hpp"
#include "output/outputwriter.hpp"
#include "queue/queue.hpp"

/* Global variables */
extern std::string INPUT_FILE_PATH;
extern DM_Input dminput;

extern OutputWriterList dmoutput;

/* Basic parameters */
extern double t_now, t_lim, delta_t;
extern int mol_no;
extern double ximin[3], ximax[3];
extern double x1min, x1max, x2min,x2max, x3min, x3max; //box boundaries

/* Particle states */
extern std::vector<vec3> POS;
extern std::vector<vec3> VEL;
extern std::vector<vec3> ACL;
extern std::vector<int> TYPE;
extern std::vector<double> MASS;

extern double SIGMA[10][10];
extern double EPSILON[10][10];


/* Energy and Temperature */
#define SYS_KE 0 /* System KE */
#define SYS_PE 1 /* System PE */
extern double EN[2];
extern double TEMP;
extern Queue AVG_EN[2];

/* Berendsen thermostat */
extern bool BEN_ENABLE;
extern double BEN_TEMP;
extern double BEN_TAU; 

/* Sweep and Prune */
/* Source: https://github.com/mattleibow/jitterphysics/wiki/Sweep-and-Prune */
extern double SP_CUTOFF; /* Cut-off for sweep and prune. Should be half the size of bounding rect */
extern bool SP_ENABLE;
extern std::vector<std::tuple<int,int>> SP_CHECKPAIRS;
extern std::array<std::vector<int>,3> SP_AxisList;
bool SweepPrune_Init();
bool SweepPrune_Sort();
bool SweepPrune_CheckIntersect();

/* Boundary Conditions */
bool Impose_BCs(vec3& pos, vec3& vel);


bool Core_Init(int argc, char* argv[]);
bool Problem_Init();
bool Step_Time();
bool After_Step();