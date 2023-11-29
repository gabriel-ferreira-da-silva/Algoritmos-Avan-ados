#include<iostream>
#include<vector>
#include<cmath>
// creates the pre processed table


#define WIDTH  10000
#define HEIGHT 1000

#define A_ 1664525
#define C_ 1013904223
#define R_ 4294967296


#define MIN 0
#define MAX 4294967295

long long int table[HEIGHT][WIDTH];
long long int A[WIDTH];


void createTable( long long int (*func) (long long int, long long int) , long long int N ){
    int m = (long long int) log2(N) + 1;

    for(long long int i =0; i < N ; i++){
        table[0][i] = A[i];
    }

    int k = 1;
    for(int i =1 ; i < m ; i++){
        for(int j=0; j < N ; j++){
            if(j+k < N){
                table[i][j] = func(table[i-1][j], table[i-1][j+k]);
                //table[i][j] = table[i-1][j] + table[i-1][j+k];
            }else{
                table[i][j] = table[i-1][j];
            }
        }
        k*=2;
    }
}

long long int query(long long int (*func) (long long int, long long int) ,long long int N, long long int left, long long int right, long long int neutro){
    long long int ans = neutro;
    int i;
    while(left < right){
        i = (long long int) log2(right-left);
        ans = func(ans , table[i][left]);
        left= left + pow(2, i);
    }

    return ans;
}

void update(long long int (*func) (long long int, long long int) ,long long int N, long long int j, long long int val, long long int neutro){
    table[0][j]= val;
    long long int k=1;
    long long int m = (long long int) log2(N) +1;
    for(long long int i=1; i<m ; i++){
        for(long long int left =( (0 > j-2*k +1) ? 0 :j-2*k +1 ); left <= j ; left++){
            table[i][left] = func(table[i-1][left], table[i-1][left+k]);
            //table[i][left] = table[i-1][left] + table[i-1][left+k];
        }
        k*=2;
    }
}

std::vector<std::vector<int>> createTable_( int (*func) (std::vector<int> , int , int ) , int (*mu) (int,int),int neutro, std::vector<int> A ){
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

std::vector<std::vector<int>> updateTable(std::vector<std::vector<int>> table,int (*func) (std::vector<int> , int , int ) , int (*mu) (int,int), int j, int val){
    table[0][j]  = val;
    int k=1;
    for(int i =1; i < table.size();i++){
        for(int l = (0 > j-2*k +1 ? 0: j-2*k +1) ; l <=j; l++ ){
            table[i][l] = table[i-1][l] + table[i-1][l+k];
            std::cout << "mu(" <<table[i-1][l]<< ","<< table[i-1][l+k] << ") = " << mu(table[i-1][l], table[i-1][l+k]) <<"\n" ;
        }
        k = k*2;
    }
    return table;
}

/*sum*/
std::vector<std::vector<long long int>> createTableSum( std::vector<long long int> A ){
    int m = (int) log2(A.size()) + 1;
    int n = A.size();
    std::vector<std::vector<long long int>> table;

    for(int i=0; i < m; i++){
        std::vector<long long int> column;
        for(int j=0; j < n ; j++){
            column.push_back(0);
        }
        table.push_back(column);        
    }

    for(int i=0; i < n; i++){
        table[0][i] = A[i];
    }

    int k=1;
    for(int i=1; i < m; i++){
        for(int j=0; j < n ; j++){
            if(j+k < n){
                table[i][j] = table[i-1][j] + table[i-1][j+k];
            }else{
                table[i][j] = table[i-1][j] + 0;
            }
            
        }
        k = k*2;
    }
    return table;
}

long long int querySum( std::vector<std::vector<long long int>> table, int left, int right){
    long long int ans=0;
    while(left<right){
        int i = log2(right -left);
        ans = ans + table[i][left];
        left = left + pow(2, i);
    }
    return ans;
}

std::vector<std::vector< long long int>> updateSum(std::vector<std::vector<long long int>> table, long long int j,long long int val){
    table[0][j]  = val;
    int k=1;
    for(int i =1; i < table.size();i++){
        for(int l = (0 > j-2*k +1 ? 0: j-2*k +1) ; l <=j; l++ ){
            table[i][l] = table[i-1][l] + table[i-1][l+k];
        }
        k = k*2;
    }
    return table;
}

/*min*/
std::vector<std::vector<int>> createTableMin( std::vector<int> A ){
    int m = (int) log2(A.size()) + 1;
    int n = A.size();
    std::vector<std::vector<int>> table;

    for(int i=0; i < m; i++){
        std::vector<int> column;
        for(int j=0; j < n ; j++){
            column.push_back(9999999);
        }
        table.push_back(column);        
    }

    for(int i=0; i < n; i++){
        table[0][i] = A[i];
    }
    int k=1;
    for(int i=1; i < m; i++){
        for(int j=0; j < n ; j++){
            if(j+k < n){
                table[i][j] = table[i-1][j]  < table[i-1][j+k] ? table[i-1][j]  : table[i-1][j+k];
            }else{
                table[i][j] = table[i-1][j];
            }
            
        }
        k = k*2;
    }
    return table;
}


int queryMin( std::vector<std::vector<int>> table, int left, int right){
    int ans= 99999999;
    while(left<right){
        int i = log2(right -left);
        ans = ans < table[i][left] ? ans : table[i][left];
        left = left + pow(2, i);
    }
    return ans;
}

std::vector<std::vector<int>> updateMin(std::vector<std::vector<int>> table, int j, int val){
    table[0][j]  = val;
    int k=1;
    for(int i =1; i < table.size();i++){
        for(int l = (0 > j-2*k +1 ? 0: j-2*k +1) ; l <=j; l++ ){
            table[i][l] = table[i-1][l] < table[i-1][l+k] ?table[i-1][l] :  table[i-1][l+k] ;
        }
        k = k*2;
    }
    return table;
}

/*max*/

std::vector<std::vector<int>> createTableMax( std::vector<int> A ){
    int m = (int) log2(A.size()) + 1;
    int n = A.size();
    std::vector<std::vector<int>> table;

    for(int i=0; i < m; i++){
        std::vector<int> column;
        for(int j=0; j < n ; j++){
            column.push_back(-9999999);
        }
        table.push_back(column);        
    }

    for(int i=0; i < n; i++){
        table[0][i] = A[i];
    }
    int k=1;
    for(int i=1; i < m; i++){
        for(int j=0; j < n ; j++){
            if(j+k < n){
                table[i][j] = table[i-1][j]  > table[i-1][j+k] ? table[i-1][j]  : table[i-1][j+k];
            }else{
                table[i][j] = table[i-1][j];
            }
            
        }
        k = k*2;
    }
    return table;
}


int queryMax( std::vector<std::vector<int>> table, int left, int right){
    int ans= -99999999;
    while(left<right){
        int i = log2(right -left);
        ans = ans > table[i][left] ? ans : table[i][left];
        left = left + pow(2, i);
    }
    return ans;
}

std::vector<std::vector<int>> updateMax(std::vector<std::vector<int>> table, int j, int val){
    table[0][j]  = val;
    int k=1;
    for(int i =1; i < table.size();i++){
        for(int l = (0 > j-2*k +1 ? 0: j-2*k +1) ; l <=j; l++ ){
            table[i][l] = table[i-1][l] > table[i-1][l+k] ?table[i-1][l] :  table[i-1][l+k] ;
        }
        k = k*2;
    }
    return table;
}
