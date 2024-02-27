#include<iostream>
#include<vector>
using namespace std;
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

void precursors(Skiplist *sl, long long int key){
    long long int  h = sl->height;
    
    if(prec.size()<sl->height){
        prec.resize(sl->height, NULL);
    }
    
    //cout<<"cuzinho1";
    Node* cur = sl->head;
    for(long long int l= h-1; l >=0 ; l--){
        while(cur!=NULL && cur->next[l] != NULL && cur->next[l]->key < key){
            cur = cur->next[l];
        }
        prec[l] = cur;
    }
}

void insert(Skiplist *sl, long long int key, long long int height){
    precursors(sl, key);
    if(prec[0]->next[0] != NULL && prec[0]->next[0]->key == key){
        return;
    }
    if(height > sl->height){
        for(long long int i =sl->height; i < height ;i++){
                sl->head->next.push_back(NULL);
                sl->head->height = sl->head->next.size();
            }
            for(long long int i =sl->height; i < height ;i++){
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
    precursors(sl,key);
    if(prec[0]->next[0]==NULL || prec[0]->next[0]->key !=key ){
        return;
    }
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

int main(){
    Skiplist sl;
    
    precursors(&sl , 123453);
    precursors(&sl , 1145);
    precursors(&sl , 6583);
    precursors(&sl , 7813);
    precursors(&sl , 12343);
    precursors(&sl , 11234);

    
    insert(&sl ,1,1);
    insert(&sl ,10,1);
    insert(&sl ,5,4);
    insert(&sl ,6,1);
    insert(&sl ,4,3);
    insert(&sl ,7,7);
    insert(&sl ,3,2);
    show(sl);
    showprec(&sl, 3);
    showhead(&sl);
    
    insert(&sl ,91,1);
    insert(&sl ,41,5);
    insert(&sl ,34,2);
    cout<<"\n\n";
    show(sl);
    remove(&sl, 34);
    remove(&sl, 2);
    remove(&sl, 7);
    remove(&sl, 34);
    remove(&sl, 1);
    remove(&sl, 6);
    cout<<"\n\n";
    show(sl);
    show(sl);

}