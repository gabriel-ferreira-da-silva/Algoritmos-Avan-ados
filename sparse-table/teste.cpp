#include<iostream>
#include "sparse-table.h"
#include<vector>
#include<cstdlib>

int sum_mu(int a, int b){
    return a+b;
}

int sum(std::vector<int> A,int start, int end){
    int sum=0;
    for(int i =start; i < end && i < A.size();i++){
        sum+=A[i];
    }
    return sum;
}

int min_mu(int a, int b){
    return a < b ? a : b;
}

int min(std::vector<int> A,int start, int end){
    int m=A[start];
    for(int i =start; i < end && i < A.size();i++){
        m = A[i] < m ? A[i]: m;
    } 
    return m;
}


int main(){
    std::cout << "hello ao\n";
    std::vector<int> A;
    /*for(int i=0; i < 10; i++){
        A.push_back(rand()%15);
    }*/
    A.push_back(1);
    A.push_back(10);
    A.push_back(3);
    A.push_back(5);
    A.push_back(6);
    A.push_back(11);
    A.push_back(7);
    A.push_back(4);
    A.push_back(4);

    std::cout << "soma\n";
    std::vector< std::vector<int>> table = createTable(sum,sum_mu,0,A);

    for(int i=0; i < table.size() ;i++){
        for(int j=0; j<table[0].size(); j++){
            std::cout<< table[i][j] <<" ";
        }
        std::cout<< "\n";
    }

    std::cout <<"query: " << rangeQuery(table, sum_mu, 0,3,7)<< "\n";

    std::cout << "minimo\n";
    table = createTable(min,min_mu,99999,A);

    for(int i=0; i < table.size() ;i++){
        for(int j=0; j<table[0].size(); j++){
            std::cout<< table[i][j] <<" ";
        }
        std::cout<< "\n";
    }

    std::cout <<"query: " << rangeQuery(table, min_mu, 10000,3,7)<< "\n";



}