#include "./input_reader.hpp"
#include <iostream>
#include <stdexcept>

// Open and parse input file
bool DM_Input::open(std::string file_path) {
    fp = fopen(file_path.c_str(),"r");
    if(!fp){
        printf("[Error] DM_Input::open : Unable to open %s\n",file_path.c_str());
        return false;
    } 
    
    char raw_line[500];
    int line_count = 0;
    bool error = false;
    while(fgets(raw_line,sizeof(raw_line),fp) && !error){
        line_count ++;
        std::string raw = std::string(raw_line);
        std::string line = strip(raw);


        if(line[0] == '#' || line.length() == 0) 
            continue; //skip comments & empty lines

        std::vector<std::string> pair = split(line,'#'); // Remove line comments  
        line = pair[0];

        pair = split(line,'=');

        if(pair.size() == 2) {
            std::string key = strip(pair[0]);
            std::string val = strip(pair[1]);
            printf("[%s]:[%s]\n",key.c_str(),val.c_str());
            //std::pair<std::string,std::string>(key,val);
            params.insert(std::make_pair(key,val)); //insert key-value pair
        } else {
            printf("[Error] DM_Input::open : Invalid formatting at line %d\n",line_count);
            error = true;
        }
    }
    fclose(fp);
    return !error;
}

int DM_Input::GetInt(std::string name) {
    auto result = params.find(name);
    if(result == params.end()){
        printf("[Error] DM_Input::GetReal : Key %s not found!\n",name.c_str());
        throw std::runtime_error(
            std::string("[Error] DM_Input::GetInt : Key ") + name +
            std::string(" not found!")); 
    }
    return std::stoi(result->second);
}

int DM_Input::GetOrSetInt(std::string name,int def) {
    auto result = params.find(name);
    if(result == params.end()){
        return def;
    }
    return std::stoi(result->second);
}

double DM_Input::GetReal(std::string name) {
    auto result = params.find(name);
    if(result == params.end()){
        printf("[Error] DM_Input::GetReal : Key %s not found!\n",name.c_str());
        throw std::runtime_error(
            std::string("[Error] DM_Input::GetReal : Key ") + name +
            std::string(" not found!")); 
    }
    return std::stod(result->second);
}

double DM_Input::GetOrSetReal(std::string name, double def){
    auto result = params.find(name);
    if(result == params.end()){
        return def;
    }
    return std::stod(result->second);
}

bool DM_Input::GetBool(std::string name) {
    auto result = params.find(name);
    if(result == params.end()){
        printf("[Error] DM_Input::GetReal : Key %s not found!\n",name.c_str());
        throw std::runtime_error(
            std::string("[Error] DM_Input::GetBool : Key ") + name +
            std::string(" not found!")); 
    }

    if(result->second == "true"){
        return true;
    } else if(result->second == "false") {
        return false;
    } else {
        printf("[Error] DM_Input::GetBool : Type converstion error\n");
        throw std::invalid_argument("[Error] DM_Input::GetBool : Type converstion error");
    }
    return false;
}

bool DM_Input::GetOrSetBool(std::string name, bool def){
    auto result = params.find(name);
    if(result == params.end()){
        return def;
    }
    if(result->second == "true")
        return true;
    else if(result->second == "false")
        return false;
    else {
        printf("[Error] DM_Input::GetBool : Type converstion error\n");
        throw std::invalid_argument("[Error] DM_Input::GetBool : Type converstion error");
    }
}

std::string DM_Input::GetStr(std::string name){
    auto result = params.find(name);
    if(result == params.end()){
        printf("[Error] DM_Input::GetReal : Key %s not found!\n",name.c_str());
        throw std::runtime_error(
            std::string("[Error] DM_Input::GetStr : Key ") + name +
            std::string(" not found!")); 
    }
    return result->second;
}

std::string DM_Input::GetOrSetStr(std::string name,std::string def){
    auto result = params.find(name);
    if(result == params.end()){
        return def;
    }
    return result->second;
}

std::string DM_Input::strip(std::string line) {
    std::string strip_item = " \t\n\r";
    size_t begin=0, end=0;
    for(std::size_t i=0;i<line.length();i++){
        if(strip_item.find(line[i]) == std::string::npos){
            begin = i;
            break;
        }
    }
    for(std::size_t i=line.length()-1; i>=0; i--){
        if(strip_item.find(line[i]) == std::string::npos){
            end = i+1;
            break;
        }
    }
    if(end-begin == 0)
        return "";
    return line.substr(begin,end-begin);
}

std::vector<std::string> DM_Input::split(std::string line, char delimiter) {
    std::vector<std::string> result;
    size_t last = 0;
    for(std::size_t i=0;i<line.length();i++){
        if(line[i] == delimiter) {
            result.push_back(line.substr(last,i-last));
            last = i+1;
        }
    }
    result.push_back(line.substr(last,line.length()-last));
    return result;
}

/*char* DM_Input::strip(char* line){
    char* str = nullptr;
    while(*line != '\0' && (*line == ' ' || *line == '\t' || *line == '\n' || *line == '\r'))
        line++;
    str = line;
    while(*line != '\0') line++;
    while(line != str && (*line == '\0' || *line == ' ' || *line == '\t' || *line == '\n' || *line == '\r')) 
        line--;
    *(line+1) = '\0';
    return str;
}

int DM_Input::split(char* line, char delimiter, char* pos[], int max) {
    if(pos == NULL || max <= 0) return -1;

    int hit = 1;
    pos[0] = line;
    while(*line != '\0' && hit != max){
        if(*line == delimiter){
            *line = '\0';
            pos[hit] = line + 1;
            hit++;
        }
        line ++;
    }
    return hit;
}*/