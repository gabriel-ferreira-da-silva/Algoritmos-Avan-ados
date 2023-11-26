#include<iostream>
#include "sparse-table.h"
#include<vector>
#include<cstdlib>
#include<ctime>

using namespace std;

int sum_mu(int a, int b){
    return a+b;
}

long long int sum(std::vector<long long int> A,int start, int end){
    int sum=0;
    for(int i =start; i < end && i < A.size();i++){
        sum+=A[i];
    }
    return sum;
}


int main(){
    vector<long long int> A;

    int count =1000;
    for(int i=0 ; i < count ; i++){
        A.push_back( rand());
    }
    vector<vector<long long int>> table = createTableSum(A);
    
    for(int i=0 ; i < count; i++){
        long long int left = rand() % (count/2);
        long long int right = left + rand() % (count/2);

        if(right - left  > count/ 20){
            table = updateSum(table, left, right  * left);
            A[left] = right * left;
        }

        long long int a  = querySum(table, left, right );
        long long int b = sum(A, left, right);
        if(a!=b){
            cout << "PANIC";
            cout << "i: "<< i << " " << a << "=a is not equal to " << b << "=b \n";
        }
    }

    cout << "its okay";

}