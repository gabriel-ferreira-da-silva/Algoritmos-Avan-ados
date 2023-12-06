#include "vEBT.h"
#include<iostream>

int main(){
    vEBT a(16);

    a.insert(&a, 2);
    a.insert(&a, 10);
    a.insert(&a, 13);
    
    std::cout << a.sucessor(&a, 4) << "\n";



}