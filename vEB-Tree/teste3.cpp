
#include<iostream>
#include "vEBT-internet.h"

int main(){
    vEB tree(1 << 4);
    std::cout << "Insert 12, 10, 13, 14\n";
    tree.insert(12);
    tree.insert(10);
    tree.insert(13);
    tree.insert(14);
    tree.insert(5);
    std::cout << "Successor of 2 is\n";
    std::cout << tree.successor(2) << '\n';
    tree.remove(13);
    std::cout << "Removing 13. Now successor of 13 is\n";
    std::cout << tree.successor(13) << '\n';
    tree.remove(14);
    tree.remove(5);
    
    std::cout << "Removing 14. Now successor of 13 is\n";
    std::cout << tree.successor(13) << '\n';
    std::cout << "16, which is universe size, means no successor.\n";

    return 0;
}