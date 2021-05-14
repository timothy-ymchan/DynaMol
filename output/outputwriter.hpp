#pragma once
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <array>

#define MAX_WRITERS 20

typedef void (*WriterFunc)(FILE* fp);

typedef struct {
    std::string path = "";
    FILE* fp = nullptr;
    double t_last = 0.0, t_interval = 0.0;
    WriterFunc func = nullptr;
} OutputWriter;

class OutputWriterList {
    std::vector<OutputWriter> writers;
    //std::array<OutputWriter,MAX_WRITERS> writers;
    int len;
    public:
    OutputWriterList(){
        len = 0;
    }
    bool RegisterWriter(std::string path, double interval, WriterFunc func);
    bool WriteAll(double now,bool force=false);
    bool CloseAll();
};