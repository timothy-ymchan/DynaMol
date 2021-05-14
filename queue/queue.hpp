#ifndef _DYNAMOL_QUEUE_H_
#define _DYNAMOL_QUEUE_H_

#include <cassert>

class Queue {                       //Fixed sized queue implemented with circular buffer
    int max_size;
    double* queue;
    int q_begin, q_end, q_len;
    public:
    Queue() {
        q_begin = q_end = q_len= 0;
        max_size = 0;
        queue = nullptr;
    }
    Queue(int size) {
        q_begin = q_end = q_len = 0;
        assert((size>0));
        max_size = size;
        queue = new double[size];
    }
    ~Queue() {
        //if(queue != nullptr)
        //    delete queue;
    }

    /* Access */
    double &operator[](int i) { 
        assert((i<q_len && i>=0)); 
        return queue[(q_begin+i)%max_size];
    };
    double operator[](int i) const {
        assert((i<q_len && i>=0)); 
        return queue[(q_begin+i)%max_size];
    };

    void enqueue(double val);
    void fenqueue(double val);
    double dequeue();
    void print();
    int size() const {return q_len;};
    bool full() const {return q_len == max_size;};
    double sum(); //not really a queue feature but anyway
};

#endif