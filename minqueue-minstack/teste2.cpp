#include<iostream>
#include "minstack-minqueue.h"

int main(){
    Minqueue_Arrdin q;

    q.enqueue(10);
    q.enqueue(13);
    q.enqueue(4);
    q.enqueue(30);
    q.enqueue(23);

    printf("%lld\n", q.min());
    
    q.dequeue();
    q.dequeue();
    q.dequeue();

    
    printf("%lld\n", q.min());
    
    q.enqueue(133);
    q.enqueue(413);
    q.enqueue(32);
    q.enqueue(3);
    q.enqueue(33);

    printf("%lld\n", q.min());

    q.dequeue();
    q.dequeue();
    q.dequeue();
    q.dequeue();
    q.dequeue();
    q.dequeue();

    printf("%lld\n", q.min());
    printf("size A %d\n", q.A.size());
    printf("size M %d", q.M.size());
    
    
    q.dequeue();
    q.dequeue();
    q.dequeue();

    
}