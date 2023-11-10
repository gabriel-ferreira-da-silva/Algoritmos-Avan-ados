#include<iostream>
#include<vector>
#include<deque>
class Node {
    public:
        int val;
        Node *next;
        Node *min;

        Node(){
            next=NULL;
            min=NULL;
        }
};

class Minstack {
    public:
        Node *top  = new Node;
        

        Minstack(){
            top->next = NULL;
            top->min = top;
            top->val =9999999;
        }

        void push(int val){
            Node *n = new Node;
            n->val = val;
            if(top->next == NULL){
                n->min = n;
            }else if(top->min->val > val){
                n->min = n;
            }else{
                n->min = top->min;
            }
            n->next = top;
            top = n;
        }

        int pop(){
            if(top->next==NULL){
                return top->val;
            }else{
                Node *temp;
                int a  = top->val;
                top = top->next;
                delete temp;
                return a;
            }
        }


        int showMin(){
            return top->min->val;          
        }

};



class Minqueue{
    public:
        Minstack front, rear;

        void enqueue(int val){
            rear.push(val);
        }

        int pop(){
            return rear.pop();
        }

        int dequeue(){
            if(front.top->next == NULL){
                while(rear.top->next != NULL){
                    front.push(rear.pop());
                }
            }

            return front.pop();
        }

        int showFirst(){
            if(front.top->next == NULL){
                while(rear.top->next != NULL){
                    front.push(rear.pop());
                }
            }

            return front.top->val;
        }

        int showMin(){
            return (front.showMin() < rear.showMin()) ? front.showMin() : rear.showMin();
        }



};

class Minqueue_Arrdin{
    public:
        std::vector<long long int> A, M;

        void enqueue(long long int value){
            A.push_back(value);
            while( M.size()> 0 && M.back() > value){
                M.pop_back();
            }
            M.push_back( value );
        }

        long long int dequeue(){
            long long int value = A[0];

            if( M.size() > 0 && value == M[0]){
                M.erase(M.begin());
            }

            if( A.size() > 0 ){
                A.erase(A.begin());
            }
            
        }

        long long int min(){
            return M[0];
        }

};

class Minqueue_Arrdin_Index{
    public:
        std::vector<long long int> A, M;

        void enqueue(long long int value){
            A.push_back(value);
            while( M.size() > 0 && A[M.back()] > value){
                M.pop_back();
            }
            M.push_back( A.size() - 1 );
        }

        long long int dequeue(){
            long long int value = A[0];

            if( M.size() > 0 && value == A[M[0]]){
                M.erase(M.begin());
            }
            
            //  A OPERAÇÃO DE DEQUEUE É O(N) POR 
            //  SER NECESSÁRIO ATUALIZAR OS IND-
            //  CES DE M

            if( A.size() > 0 ){
                A.erase(A.begin());
                for(int i=0; i < M.size() ; i++){
                    M[i] -= 1;
                }
            }
            
        }

        long long int min(){
            return A[M[0]];
        }

};


class Minqueue_queue{
    public:
        std::deque<unsigned long int> V,M;

        void enqueue(unsigned long int val){
            V.push_back(val);
            while( M.size() > 0 && V[M.back()] > val){
                M.pop_back();
            }
            M.push_back(V.size()-1);
        }

        unsigned long int dequeue(){
            if(V.size()>0){
                unsigned long int val = V[0];
                V.pop_front();
                if( 0 == M.front()){
                    M.pop_front();
                }
                for(unsigned long int i=0 ; i < M.size() ; i++){
                    M[i] = M[i]-1;
                }
                return val;

            }
            return 0;
        }

        void show(){

            std::cout << "V: \n";
            for(int i =0; i < V.size() ; i++){
                std::cout << V[i] << " ";
            }
            std::cout << "\nM: \n";
            for(int i =0; i < M.size() ; i++){
                std::cout << M[i] << " ";
            }
            std::cout << "\nV[M]: \n";
            for(int i =0; i < M.size() ; i++){
                std::cout << V[M[i]] << " ";
            }
            std::cout <<"\n";
        }

};