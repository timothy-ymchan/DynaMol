#include "outputwriter.hpp"

bool OutputWriterList::RegisterWriter(std::string path, double interval, WriterFunc func){
    /*if(len == MAX_WRITERS) {
        printf("[Error] OutputWriterList::RegisterWriter: Writer limit reached!\n");
        return false;
    }
    
    writers.push_back(OutputWriter());
    writers[len].path = path;
    writers[len].fp = fopen(path.c_str(),"w");
    if(writers[len].fp == nullptr){
        printf("[Error] OutputWriterList::RegisterWriter: Failed to open %s\n",path.c_str());
        return false;
    }
    writers[len].t_last = 0;
    writers[len].t_interval = interval;
    writers[len].func = func;

    len ++;
    */
    OutputWriter newWriter; 
    
    newWriter.path = path;
    newWriter.fp = fopen(path.c_str(),"w");
    if(newWriter.fp == nullptr) {
        printf("[Error] OutputWriterList::RegisterWriter: Failed to open %s\n",path.c_str());
        return false;
    }
    newWriter.t_last = 0;
    newWriter.t_interval = interval;
    newWriter.func = func;

    writers.push_back(newWriter);
    return true;
}

bool OutputWriterList::WriteAll(double now,bool forced) {
    for(std::size_t i = 0; i < writers.size(); i++){
        if(now - writers[i].t_last > writers[i].t_interval || forced) {
            
            printf("Writer %d\t%lf\t%lf\t%lf\n",(int)(i+1),now,writers[i].t_last,writers[i].t_interval);
            writers[i].func(writers[i].fp);
            writers[i].t_last = now;
        }
    }
    /*for(int i = 0; i < len; i++){
        if(now - writers[i].t_last > writers[i].t_interval || forced) {
            
            printf("Writer %d\t%lf\t%lf\t%lf\n",i,now,writers[i].t_last,writers[i].t_interval);
            writers[i].func(writers[i].fp);
            writers[i].t_last = now;
        }
    }*/

    return true;
}

bool OutputWriterList::CloseAll() {
    for(std::size_t i=0;i<writers.size();i++){
        if(writers[i].fp != nullptr) {
            fclose(writers[i].fp);
        } else {
            printf("[Warning] Writer of %s is null when closing!\n",writers[len].path.c_str());
        }
    }
    /*for(int i=0;i<len;i++){
        if(writers[i].fp) {
            fclose(writers[i].fp);
        } else {
            printf("[Warning] Writer of %s is null when closing!\n",writers[len].path.c_str());
        }
    }*/
    return true;
}