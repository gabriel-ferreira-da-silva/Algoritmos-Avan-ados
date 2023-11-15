#include<iostream>
#include<vector>
#include<cmath>
// creates the pre processed table

std::vector<std::vector<int>> createTable( int (*func) (std::vector<int> , int , int ) , int (*mu) (int,int),int neutro, std::vector<int> A ){
    int m = (int) log2(A.size()) + 1;
    int n = A.size();
    std::vector<std::vector<int>> table;

    for(int i=0; i < m; i++){
        std::vector<int> column;
        for(int j=0; j < n ; j++){
            column.push_back(neutro);
        }
        table.push_back(column);        
    }

    for(int i=0; i < n; i++){
        table[0][i] = func(A, i, i+1 );
    }
    int k=1;
    for(int i=1; i < m; i++){
        for(int j=0; j < n ; j++){
            if(j+k < n){
                table[i][j] = mu( table[i-1][j], table[i-1][j+k]);
            }else{
                table[i][j] = mu( table[i-1][j], neutro);
            }
            
        }
        k = k*2;
    }
    return table;
}


int rangeQuery( std::vector<std::vector<int>> table, int (*mu) (int,int) , int neutro, int left, int right){
    int ans=neutro;
    while(left<right){
        int i = log2(right -left);
        ans = mu(ans, table[i][left]);
        left = left + pow(2, i);
    }
    return ans;
}