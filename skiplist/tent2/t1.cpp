#include<iostream>
#include<vector>
using namespace std;

#define R 4294967296
#define A 1664525
#define C 1013904223

long long int n_visited;
long long int n_height;
long long int res;

class Node{
    public:
        long long int key;
        long long int height;
        std::vector<Node*> next;
};


class Skiplist{
    public:
        Node* head= new Node;
        long long int height;

        Skiplist(){
            head->next.push_back(NULL);
            head->height = 1;
            head->key = -99999999;
            height = 1;
        }
};

vector<Node*> prec;
Node* cur = new Node;




class glc{
    public:
        long long int x;
        void set(long long int s){
            x=s;
        }
        long long int next(){
            long long int x1;
            x1=x;
            x = (A*x + C)%R;
            return x1;
        }
};

glc rng;
long long int random_height(long long int hmax){
    long long int h =1;
    hmax++;
    while( (rng.next() % 100 < 50 ) && h < hmax){
        h++;
    }
    return h;
}


void precursors(Skiplist *sl, long long int key){
    long long int  h = sl->height;
    n_visited=0;
    n_height=0;
    if(prec.size()<sl->height){
        prec.resize(sl->height, NULL);
    }
    
    //cout<<"cuzinho1";
    Node* cur = sl->head;
    for(long long int l= h-1; l >=0 ; l--){
        while(cur!=NULL && cur->next[l] != NULL && cur->next[l]->key < key){
            cur = cur->next[l];
            n_visited++;
        }
        prec[l] = cur;
    }
    if(prec[0]!= NULL && prec[0]->next[0] != NULL){
        n_height = prec[0]->next[0]->height;
    }else{
        n_height = 0;
    }
}

Node* find(Skiplist *sl, long long int key){
    precursors(sl, key);
    if(prec[0]->next[0] != NULL && prec[0]->next[0]->key == key){
        return prec[0]->next[0];
    }else{
        n_height=0;
        return NULL;
    }
}

void insert(Skiplist *sl, long long int key){
    res=0;
    precursors(sl, key);
    if(prec[0]->next[0] != NULL && prec[0]->next[0]->key == key){
        return;
    }
    res=1;
    long long int height = random_height(sl->height);
    if(height > sl->height){
        for(long long int i =sl->height; i < height ;i++){
                sl->head->next.push_back(NULL);
                sl->head->height = sl->head->next.size();
                prec.push_back(sl->head);
        }
        sl->height = height;
    }
    Node *n = new Node;
    vector<Node*> a(height, NULL);
    n->height = height;
    n->key  = key;
    n->next = a;
    for(long long int l = 0; l < height ; l++){
        n->next[l] = prec[l]->next[l];
        prec[l]->next[l] = n;
    }
}
void remove(Skiplist *sl, long int key){
    res=0;
    precursors(sl,key);
    if(prec[0]->next[0]==NULL || prec[0]->next[0]->key !=key ){
        return;
    }
    res = 1;
    Node* n = prec[0]->next[0];
    for(long long int l=0; l < n->height ; l++){
        prec[l]->next[l] = n->next[l];
    }
    while(sl->height > 1 && sl->head->next[sl->height -1]==NULL){
        sl->head->next.pop_back();
        sl->height = sl->height -1;
        sl->head->height = sl->height;
    }
    sl->head->height = sl->height;
}


void show(Skiplist sl){
    cout<< "height "<<sl.height << "\n";
    for(long long int i = (sl.height-1); i >= 0 ; i--){
        cur =sl.head;
        while(cur != NULL && cur->next[i] != NULL){
            cout << cur->next[i]->key <<" ";
            cur = cur->next[i];
        }
        cout <<"\n";
    }
}



void showprec(Skiplist *sl, long long int k){
    precursors(sl, k);
    for(long long int i = 0; i < sl->height ; i++){
        cout << prec[i]->key<<" ";
    }
    cout<<"\n";
}

void showhead(Skiplist *sl){

    for(long long int i = 0; i < sl->height ; i++){
        cout << sl->head->next[i]->key<<" ";
    }
    cout<<"\n";
}
long long int next(long long int s){
    return (s*A + C)%R;
}



int main(){
    Skiplist sl;
    long long int S,U,B,N, F,I, D,P;
    scanf(" %lld %lld %lld %lld %lld %lld %lld %lld", &S, &U, &B, &N, &F, &I, &D, &P);
    rng.set(S);
    long long int x;
    
    
    for(long long int i=0 ; i < B; i++){
        insert(&sl, rng.next()%U);
    }

    for(long long int i=0 ; i < N; i++){
        x = rng.next() % (F+I+D);
        //cout<<i%P << "cuuuuuuuuuuuuuuuuuuuuuuuu\n";
        if(x < F){
            x = rng.next()%U;
            find(&sl, x);
            
            if(i%P==0){
                cout<<"F "<<n_visited+1 <<" "<< n_height<<"\n";
            }
        }else if(F<= x && x < F+I){
            x = rng.next()%U;
            insert(&sl, x);
            if(i%P==0){
                cout<<"I "<<res <<"\n";
            }
        }else{
            x = rng.next()%U;
            remove(&sl, x);
            if(i%P==0){
                cout<<"D "<< res <<"\n";
            }
        }
    }
}