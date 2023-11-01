#include<iostream>
#include "minstack-minqueue.h"

int main(){
    Minstack ms;
    Minqueue mq;

    mq.enqueue(30);
    mq.enqueue(5);
    mq.enqueue(10);

    printf("first: %d\n", mq.showFirst() );
    printf("min: %d\n", mq.showMin() );
    
    mq.dequeue();
    mq.dequeue();
    mq.enqueue(1);
    mq.enqueue(100);

    printf("first: %d\n", mq.showFirst() );
    printf("min: %d\n", mq.showMin() );
    
    //printf("first: %d min: %d", mq.showFirst(), mq.showMin());


    


}