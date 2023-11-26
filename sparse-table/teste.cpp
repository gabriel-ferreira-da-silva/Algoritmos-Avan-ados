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

int max_mu(int a , int b){
    return a > b? a : b;
}

int max(std::vector<int> A,int start, int end){
    int m=A[start];
    for(int i =start; i < end && i < A.size();i++){
        m = max_mu(m, A[i]);
    } 
    return m;
}

int main(){
    std::cout << "hello ao\n";
    std::vector<int> A;
    /*for(int i=0; i < 10; i++){
        A.push_back(rand()%15);
    }*/
    A.push_back(2);
    A.push_back(1);
    A.push_back(3);
    A.push_back(5);
    A.push_back(6);
    A.push_back(11);
    A.push_back(7);
    A.push_back(4);
    A.push_back(9);
    A.push_back(2);
    
    /*
    A.push_back(16);
    A.push_back(8);
    A.push_back(6);
    A.push_back(23);
    */
    

    std::cout << "soma\n";
    std::vector< std::vector<int>> table_sum = createTable(sum,sum_mu,0,A);
    std::vector< std::vector<int>> table_min = createTable(min,min_mu,-9999999,A);
    std::vector< std::vector<int>> table_max = createTable(max,max_mu, 9999999,A);

    
    for(int i=0; i < A.size() ;i++){
        std::cout<< A[i] <<" ";
    }
    int a,b,c;


    std::cout<< "\nstate your limitrs\n";
    std::cin >>a;
    std::cin >>b;
    std::cin >>c;

    while(a!=-1){     
        switch (a)
        {
        case 1:
            /* code */
            table_sum  = updateTable(table_sum, max, max_mu, b, c);
            break;
        
        case 2:

            for(int i=0; i < table_sum.size() ;i++){
                for(int j=0; j < table_sum[0].size() ;j++){
                    std::cout << table_sum[i][j] <<" ";
                }
                std::cout <<"\n";
            }
            
            std::cout <<"\nquery sum: " << rangeQuery(table_sum, sum_mu, 0,b,c)<< "\n";
            std::cout <<"query min: " << rangeQuery(table_min, min_mu, 10000,b,c)<< "\n";
            std::cout <<"query max: " << rangeQuery(table_max, max_mu, -10000,b,c)<< "\n";
            break;
        }
        std::cout<< "\nstate your limitrs\n";
        std::cin >>a;
        std::cin >>b;
        std::cin >>c;
    }



}