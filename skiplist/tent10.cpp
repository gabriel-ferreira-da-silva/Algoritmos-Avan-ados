#include<iostream>
#include<vector>
#include<cmath>

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

long long int init_vector(long long int s, long long int n){
    A[0] = (s % (4*n));
    long long int x =s;
    for(long long int i =1 ; i < n ; i++){
        x = (A_*x + C_) % R_;
        A[i] = x%(4*n);
    }
    return x;
}

long long int sum(long long int a , long long int b){
    return a +b;
}


long long int min(long long int a , long long int b){
    return a < b ? a :b;
}


long long int max(long long int a , long long int b){
    return a > b ? a :b;
}


int main(){
    long long int S,N,O,Q,U;
    std::string F;

    int count =0;

    while(1){
        std::cin >> S>> N>> F >> O >> Q >> U;
        if(std::cin.eof()){
            exit(0);
        }
        long long int x = init_vector(S,N);
        std::cout << "caso "<< count++ << "\n";
        if(F[1]=='U'){
            createTable(sum,N);
            for(long long int i=0; i < O ; i++){
                x = (A_*x + C_) % R_;
                if( (x % (Q+U) ) < Q){
                   x = (A_*x + C_) % R_;
                   long long int left = x % N;
                   x = (A_*x + C_) % R_;
                   long long int right = left + 1 + (x % (N-left));
                   std::cout<< query(sum,N, left, right, 0) << "\n";
                }else{
                   x = (A_*x + C_) % R_;
                   long long int I = x % N;
                   x = (A_*x + C_) % R_;
                   long long int V = x % (4*N);
                   update(sum,N,I,V,0);
                   std::cout<<query(sum,N, I, N, 0) << "\n";
                }

            }
        }else if(F[1]=='A'){
            createTable(max,N);
            for(long long int i=0; i < O ; i++){
                x = (A_*x + C_) % R_;
                if( (x % (Q+U) ) < Q){
                   x = (A_*x + C_) % R_;
                   long long int left = x % N;
                   x = (A_*x + C_) % R_;
                   long long int right = left + 1 + (x % (N-left));
                   std::cout<< query(max,N, left, right, MIN) << "\n";
                }else{
                   x = (A_*x + C_) % R_;
                   long long int I = x % N;
                   x = (A_*x + C_) % R_;
                   long long int V = x % (4*N);
                   update(max,N,I,V,MIN);
                   std::cout<< query(max,N, I, N, MIN) << "\n";
                }

            }
        }else{
            createTable(min,N);
            for(long long int i=0; i < O ; i++){
                x = (A_*x + C_) % R_;
                if( (x % (Q+U) ) < Q){
                   x = (A_*x + C_) % R_;
                   long long int left = x % N;
                   x = (A_*x + C_) % R_;
                   long long int right = left + 1 + (x % (N-left));
                   std::cout<< query(min,N, left, right, MAX) << "\n";
                }else{
                   x = (A_*x + C_) % R_;
                   long long int I = x % N;
                   x = (A_*x + C_) % R_;
                   long long int V = x % (4*N);
                   update(min,N,I,V,MAX);

                   std::cout << query(min,N, I, N, MAX) << "\n";
                }

            }
        }
        
        std::cout << "\n";
    }
}