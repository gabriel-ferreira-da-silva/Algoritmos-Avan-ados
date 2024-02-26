#include<iostream>
#include<vector>
#include<deque>

#define R 4294967296
#define A 1664525
#define C 1013904223

//O objetivo deste exercício é implementar uma MinQueue para inteiros sem sinal de 32 bits 
class Minqueue{
    public:
        std::deque<unsigned long int> V,M;

        void enqueue(unsigned long int val){
            V.push_back(val);
            while( M.size() > 0 && V[M.back()] > val){
                M.pop_back();
            }
            M.push_back(V.size()-1);
        }

        void dequeue(){
            if(V.size()>0){
                unsigned long int val = V[0];
                V.pop_front();
                if( 0 == M.front()){
                    M.pop_front();
                }
                for(unsigned long int i=0 ; i < M.size() ; i++){
                    M[i] = M[i]-1;
                }
            }
        }

        unsigned long int back(){
            return V.back();
        }

        void show(){

            std::cout << "V:  ";
            for(int i =0; i < V.size() ; i++){
                std::cout << V[i] << " ";
            }
            std::cout << "\nM:  ";
            for(int i =0; i < M.size() ; i++){
                std::cout << M[i] << " ";
            }
            std::cout << "\nV[M]:  ";
            for(int i =0; i < M.size() ; i++){
                std::cout << V[M[i]] << " ";
            }
            std::cout <<"\n";
        }

};

unsigned long int next(unsigned long int x){
    return (A * x + C) % R;
}


int main(){
    
    unsigned long int S,B,N,P;

    std::cin >> S >> B >> N >> P;

    Minqueue mq;
    std::vector<unsigned long int> X;

    // BURN IN

    X.push_back(S);
    for(int i=0; i < B+N ; i++){
        X.push_back( next(X.back()));
    }

    for(int i=0; i < B ; i++){
        mq.enqueue(X[i]);
    }
    
    
    for(int i=B; i < N+B; i++){
        
        if((X[i] %10 )< P ){
            mq.enqueue(X[i+1]);
        }else{
            mq.dequeue();
        }
        printf("%ld %lu\n",mq.M.size(), mq.M.front());
        //printf("%ld %lu\n",mq.M.size(), mq.M.front());
    }

    

    

}