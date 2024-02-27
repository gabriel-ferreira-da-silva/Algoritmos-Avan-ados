#include<iostream>
#include<vector>
#include<cmath>

#define R 4294967296
#define A 1664525
#define C 1013904223

class Node{
    public:
        long long int key;
        long long int height;
        std::vector<Node*> next;
};

class Skiplist{
    public:
        long long int height;
        Node *head;

        long long delete_res;
        long long insert_res;
        long long find_nodes;
        long long find_height;
        

        Skiplist(){
            head = new Node;
            head->height=1;
            head->key=-999999;
            head->next.push_back(NULL);
        }
};

std::vector<Node*> p;


std::vector<Node*> precursors(Skiplist *l, long long int key){
    p.resize(l->height, NULL);
    Node* cur = l->head;
    l->find_nodes=1;
    for(int i = l->height -1; i >=0; i++){
        while(cur->next[i] != NULL && cur->next[i]->key < key){
            cur = cur->next[i];
            l->find_nodes++;
        }
        p[i] = cur;
    }
    if(p[0]!= NULL && p[0]->next[0] != NULL){
        l->find_height = p[0]->next[0]->height;
    }else{
        l->find_height = 0;
    }
    return p;
}

long long int random_height(Skiplist *L){
    return L->height+1;
}

void insert(Skiplist *L , long long int key){
    p = precursors(L, key);
    if(p[0]->next[0] != NULL && p[0]->next[0]->key == key){
        p[0]->next[0]->key = key;
        L->insert_res =0;
        return;
    }
    L->insert_res =1;
    long long int h = random_height(L);
    if(h > L->height){
        for(long long int i= L->height; i<h ; i++){
            L->head->next.push_back(NULL);
            p.push_back(L->head);
        }
        L->height = h;   
    }
    Node* n = new Node;
    n->key = key;
    for(long long int l=0; l<h ;l++){
        n->next.push_back(p[l]->next[l]);
        p[l]->next[l] = n;
    }
}

Node* search(Skiplist *l, long long int key){
    p = precursors(l, key);
    if(p[0]->next[0]!= NULL && p[0]->next[0]->key == key){
        l->find_height = p[0]->next[0]->height;
        return p[0]->next[0];
    }else{
        l->find_height = 0;
        return NULL;
    }
}

void remove(Skiplist *L , long long int key){
    p = precursors(L, key);
    if(p[0]->next[0]==NULL || p[0]->next[0]->key !=key){
        L->delete_res = 0;
        return;
    }
    L->delete_res = 1;
    Node *n = p[0]->next[0];
    for(long long l = 0; l < L->height ; l++){
        p[l]->next[l] = n->next[l];
    }
    while(L->height > 1 && L->head->next[L->height - 1]==NULL){
        L->height = L->height -1;
    }
}

long long int next(long long int X){
    return (A * X + C) % R;
}

int main(){
    long long int S,U,B,N,F,I,D,P;
    scanf(" %lli", &S);
    scanf(" %lli", &U);
    scanf(" %lli", &B);
    scanf(" %lli", &N);
    scanf(" %lli", &F);
    scanf(" %lli", &I);
    scanf(" %lli", &D);
    scanf(" %lli", &P);

    Skiplist sl;
    long long int X=S;
    long long int k=0;

    for(long long int i= 0 ; i < B ; i++){
        insert(&sl,X%U);
        X=next(X);
    }

    long long x;
    for(long long int i=0; i < N ;i++){
        x = X % (F+I+D);
        X = next(X);

        if( x < F){
            x = X % U;
            X = next(X);
            search(&sl , x);
            if(k%P==0){
                std::cout <<"F "<<sl.find_nodes <<" "<<sl.find_height<<"\n";    
            }
            k++;
            
        }else if( F<= x < F + I){
            x = X % U;
            X = next(X);
            insert(&sl , x);
            if(k%P==0){
                std::cout <<"I "<<sl.insert_res <<"\n";    
            }
            k++;
        }else{
            x = X % U;
            X = next(X);
            remove(&sl , x);
            if(k%P==0){
                std::cout <<"I "<<sl.delete_res <<"\n"; 
            }
            k++;
        }
    }

    return 0;    
}