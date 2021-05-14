#include "input_reader.hpp"

int main() {
    DM_Input in;
    in.open("../ideal_gas.input");
    printf("%e\n",in.GetReal("kb"));
    printf("%e\n",in.GetReal("m0"));
    printf("%e\n",in.GetReal("T0"));
}