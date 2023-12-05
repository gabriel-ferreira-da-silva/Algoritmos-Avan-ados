#include "vEBT.h"
#include<iostream>

int main(){
    vEBT a(16);
    
    a.insert(&a, 4);
    std::cout << "\na.u: " << a.u <<"\n";
    std::cout << "a.min: " << a.min <<"\n";
    std::cout << "a.max: " << a.max <<"\n";

    a.insert(&a, 3);
    std::cout << "\na.u: " << a.u <<"\n";
    std::cout << "a.min: " << a.min <<"\n";
    std::cout << "a.max: " << a.max <<"\n";


    
    a.insert(&a, 10);
    std::cout << "\na.u: " << a.u <<"\n";
    std::cout << "a.min: " << a.min <<"\n";
    std::cout << "a.max: " << a.max <<"\n";

    
    a.insert(&a, 1);
    std::cout << "\na.u: " << a.u <<"\n";
    std::cout << "a.min: " << a.min <<"\n";
    std::cout << "a.max: " << a.max <<"\n";

    
    a.insert(&a, 15);
    std::cout << "\na.u: " << a.u <<"\n";
    std::cout << "a.min: " << a.min <<"\n";
    std::cout << "a.max: " << a.max <<"\n";

    a.remove(&a, 15);
    std::cout << "\na.u: " << a.u <<"\n";
    std::cout << "a.min: " << a.min <<"\n";
    std::cout << "a.max: " << a.max <<"\n";

    a.remove(&a, 1);
    std::cout << "\na.u: " << a.u <<"\n";
    std::cout << "a.min: " << a.min <<"\n";
    std::cout << "a.max: " << a.max <<"\n";

    
    a.remove(&a, 3);
    std::cout << "\na.u: " << a.u <<"\n";
    std::cout << "a.min: " << a.min <<"\n";
    std::cout << "a.max: " << a.max <<"\n";

    
    a.remove(&a, 4);
    std::cout << "\na.u: " << a.u <<"\n";
    std::cout << "a.min: " << a.min <<"\n";
    std::cout << "a.max: " << a.max <<"\n";


}