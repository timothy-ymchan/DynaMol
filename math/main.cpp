#include "matrix.hpp"

int main() {
    Matrix m1(1,3,std::vector<double>{
        1,
        2,
        3
    });

    
    Matrix m2(3,1,std::vector<double>{
       1,
       2,
       3
    });

    printf("%s\n",m1.strfy().c_str());
    printf("%s\n",(m1*m2).strfy().c_str());
    m1 = m1/m1.norm();
    printf("%lf\n",m1.norm());
    return 0;
}