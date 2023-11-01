#include<iostream>
#include "minstack.h"

using namespace std;

int main(){
    Minstack ms;
    printf("\n hello\n");
    ms.push(10);
    printf("\n%d\n", ms.stack[0]);
    ms.push(44);
    printf("\n%d\n", ms.stack[ms.stack.size()-1].min->val);
    ms.push(2);
    printf("\n%d\n", ms.showMin());
    ms.push(111);
    printf("\n%d\n", ms.showMin());
    
}