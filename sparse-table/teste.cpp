#include<iostream>
#include "sparse-table.h"
#include<vector>
#include<cstdlib>

int sum(std::vector<int> A,int start, int end){
    int sum=0;
    for(int i =start; i < end && i < A.size();i++){
        sum+=A[i];
    }
    return sum;
}


int main(){
    std::cout << "hello ao\n";
    std::vector<int> A;
    

    for(int i=0; i < 10; i++){
        A.push_back(rand()%15);
    }

    preprocess(0, A, sum);

}