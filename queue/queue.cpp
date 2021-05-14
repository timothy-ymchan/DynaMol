#include "queue.hpp"
#include <cstdio>

void Queue::enqueue(double val) {
    assert((q_len != max_size));
    q_end = (q_len != 0)?(q_end+1)%max_size:q_end;
    queue[q_end] = val;
    q_len++;
}

void Queue::fenqueue(double val) {
    if(q_len == max_size)
        dequeue();
    enqueue(val);
}

double Queue::dequeue() {
    assert((q_len != 0));
    double val = queue[q_begin];
    q_begin = (q_begin + 1)%max_size;
    q_len--;
    return val;
}

void Queue::print() {
    printf("max_len: %d\tq_begin: %d\tq_end: %d\tq_len %d\n",max_size,q_begin,q_end,q_len);
    printf("Full buffer:\n");
    for(int i=0;i<max_size;i++){
        printf("%4.1f\t",queue[i]);
    }
}

double Queue::sum() {
    double s = 0;
    for(int i=0;i<q_len;i++){
        s += queue[i];
    }
    return s;
}