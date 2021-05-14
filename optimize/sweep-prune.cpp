#include "../global.hpp"
#include <algorithm>
#include <tuple>

std::vector<std::tuple<int,int>> SP_CHECKPAIRS;
std::array<std::vector<int>,3> SP_AxisList;
double SP_CUTOFF = 0.0;
bool SP_ENABLE = false;

void PrintVector(std::vector<int> v){
    for(std::size_t i=0;i<v.size();i++){
        printf("%d ",v[i]);
    }
    printf("\n");
}

bool SweepPrune_Init() {
    /* Fill array with particle indicies */
    for(int i=0;i<3;i++){
        SP_AxisList[i] = std::vector<int>(mol_no);
        for(std::size_t j=0;j<SP_AxisList[i].size();j++){
            SP_AxisList[i][j] = j;
        }
    }

    for(int i=0;i<3;i++){
        printf("%d: ",i);
        for(std::size_t j=0;j<SP_AxisList[i].size();j++){
            printf("%d ",SP_AxisList[i][j]);
        }
        printf("\n");
    }

    return true;
}

bool SweepPrune_Sort() {
    // Sort particles along axis
    for(int k=0;k<3;k++){
        std::sort(SP_AxisList[k].begin(),SP_AxisList[k].end(),
        [&k](const int& l, const int& r){
            return POS[l][k] < POS[r][k];
        });
    }
    return true;
}

bool SweepPrune_CheckIntersect() {
    SP_CHECKPAIRS.clear();
    std::array<std::vector<std::tuple<int,int>>,3> CheckPairs;

    if(abs(t_now - 28.818000) < 2e-3) {
            for(int i=0;i<3;i++){
                printf("%d: ",i);
                for(std::size_t j=0;j<SP_AxisList[i].size();j++){
                    printf("%d ",SP_AxisList[i][j]);
                }
                printf("\n");
            }

            printf("\n");
            for(int i=0;i<3;i++){
                printf("%d: ",i);
                for(std::size_t j=0;j<SP_AxisList[i].size();j++){
                    int id = SP_AxisList[i][j];
                    printf("%8.4lf ",POS[id][i]);
                }
                printf("\n");
            }
    }

    for(int k=0;k<1;k++){ //For each axis
        std::vector<int> ActiveList;
        ActiveList.push_back(SP_AxisList[k][0]); //Put first atom into active list
        
        for(std::size_t i=1;i<SP_AxisList[k].size();i++){ //For each item in axis list

            int currentAtom = SP_AxisList[k][i]; 
            double currentHead = POS[currentAtom][k] - SP_CUTOFF;

            // Check for each item in active list
            auto activeListIt = ActiveList.begin();
            while(activeListIt != ActiveList.end()){ 
                int activeAtom = *activeListIt;
                double activeTail = POS[activeAtom][k] + SP_CUTOFF;

                if(activeTail >= currentHead) { // Might collide 
                    
                    if(currentAtom < activeAtom) {
                        CheckPairs[k].push_back(std::make_tuple(currentAtom,activeAtom));
                    } else {
                        CheckPairs[k].push_back(std::make_tuple(activeAtom,currentAtom));
                    }
                    
                    ++activeListIt;
                } else { // Subsequent atoms will not collide, remove from active list
                    activeListIt = ActiveList.erase(activeListIt); //Erase item
                }
            }

            ActiveList.push_back(currentAtom);

            if(abs(t_now - 28.818000) < 2e-3) {
                PrintVector(ActiveList);
            }
        }
    }

    /* Do one axis for the moment */
    SP_CHECKPAIRS = CheckPairs[0];

    return true;
}