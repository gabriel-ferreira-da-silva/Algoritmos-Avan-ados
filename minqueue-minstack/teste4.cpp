#include<iostream>
#include "minstack-minqueue.h"

int main(){
    Minqueue_queue mq;

    int n;

    std::cin >> n;

    for(int i =0 ; i < n ; i++){
        unsigned long int a = ((120*i + 31*(i + n)) % 57);
        
        if(a % 5){
            std::cout << a <<" ";
            mq.enqueue(a);
        }else{
            std::cout << "\ndeq: " << mq.dequeue() << "\n";
            
        }
    }

    std::cout<< "okay\n";
    std::cout << "\n";
    mq.show();
    

    
}