#ifndef _DYNAMOL_INPUT_READER_HPP_
#define _DYNAMOL_INPUT_READER_HPP_

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <map>


class DM_Input{
    std::string path;
    FILE* fp;
    std::map<std::string,std::string> params; //key-value pair of parameters in input file

    public:
    std::string strip(std::string line);
    //char* strip(char* line);
    std::vector<std::string> split(std::string line, char delimiter);
    //int split(char* line, char delimiter, char* pos[], int max);

    public:
    bool open(std::string file_path);

    int GetInt(std::string name);
    double GetReal(std::string name);
    bool GetBool(std::string name);
    std::string GetStr(std::string name);

    int GetOrSetInt(std::string name, int def);
    double GetOrSetReal(std::string name, double def);
    bool GetOrSetBool(std::string name, bool def);
    std::string GetOrSetStr(std::string name, std::string def);
};
#endif 