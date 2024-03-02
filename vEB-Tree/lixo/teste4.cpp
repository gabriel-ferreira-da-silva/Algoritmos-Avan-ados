#include "vEBT.h"
#include<iostream>

int main(){
    vEBT a(256);
    std::cout.flush();
    insert(&a, 2);
    insert(&a, 10);
    insert(&a, 13);
    insert(&a, 4);
    insert(&a, 12);
    insert(&a, 1);
    insert(&a, 3);

    std::cout << successor(&a, 1) << "\n";
    std::cout << successor(&a, 2) << "\n";
    std::cout << successor(&a, 3) << "\n";
    std::cout << successor(&a, 4) << "\n";
    std::cout << successor(&a, 10) << "\n\n";

    
    insert(&a, 15);
    insert(&a, 100);
    insert(&a, 33);
    remove(&a, 4);
    remove(&a, 10);
    remove(&a, 12);
    remove(&a, 13);
    remove(&a, 30);
    remove(&a, 12);
    remove(&a, 15);
    remove(&a,33);

    std::cout << successor(&a, 20) << "\n";
    std::cout << successor(&a, 30 ) << "\n";
    std::cout << successor(&a, 40) << "\n\n";

    
    std::cout << successor(&a, 1) << "\n";
    std::cout << successor(&a, 2) << "\n";
    std::cout << successor(&a, 3) << "\n";
    std::cout << successor(&a, 4) << "\n";
    std::cout << successor(&a, 10) << "\n\n";



}