#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

#define R 4294967296
#define A 1664525
#define C 1013904223


class GCL{
    public:
        long long int X;
        void set(long long int s){
            X=s;
        }

        long long int next(){
            long long int a=X;
            X = (A * X + C) % R;
            return a;
        }
};

GCL RNG;

class Node{
    public:
        long long int val;
        long long int key;
        long long int height;
        vector<Node*> next;
};
vector<Node*> p;
class Skiplist{
    public:
        Node *head = new Node;
        Node *cur = new Node;

        long long int height =1;
        
        long long int delete_res;
        long long int insert_res;

        long long int find_nodes;
        long long int find_height;

        Skiplist(){
            head->next.push_back(NULL);
            head->height=1;
            head->val=0;
            head->key=-9999999;
            height = 1;
        }

        vector<Node*> precursors(long long int key){
            p.resize(height, NULL);
            cur = head;
            find_nodes=0;
            for(long long int l = height-1; l >= 0 ; l--){
                while(cur->next[l] != NULL && cur->next[l]->key < key){
                    cur = cur->next[l];
                    find_nodes++;
                }
                p[l] = cur;
            }
            if(p[0]!= NULL && p[0]->next[0] != NULL){
                find_height = p[0]->next[0]->height;
            }else{
                find_height = 0;
            }
            return p;
        }


        long long int random_height(){
            long long int h=1;
            long long int max_height = height+1;
            while(RNG.next() % 100 < 50 && h<max_height){
                h+=1;
            }
            return h;
        }

        void insert(long long int key){
            //cout<<"caguei1\n";
            p = precursors(key);
            //cout<<"caguei1\n";
            if(p[0]->next[0]!= NULL && p[0]->next[0]->key == key){
                p[0]->next[0]->val=key;
                insert_res = 0;
                return;
            }
            insert_res=1;
            //cout<<"caguei2\n";
            long long int h=random_height();
            if(h > height){
                for(int i =height; i < h ;i++){
                    head->next.push_back(NULL);
                    head->height = head->next.size();
                }
                for(int i =height; i < h ;i++){
                    p.push_back(head);
                }
                height = h;
            }
            //cout<<"caguei3\n";

            Node* n = new Node();
            vector<Node*> a(h, NULL);
            n->height = h;
            n->next = a;
            n->key = key;
            n->val = key;

            for(int l =0; l<h;l++){
                n->next[l] = p[l]->next[l];
                p[l]->next[l] = n;
            }
            //cout<<"caguei4\n";

        }

        long long int search(long long int key){
            p = precursors(key);
            if (p[0]->next[0] != NULL && p[0]->next[0]->key == key ){
                find_height = p[0]->next[0]->height;
                return p[0]->next[0]->key;
            }else{
                find_height =0;
                return -1;
            }
        }

        void remove(long long int key){
            p = precursors(key);
            
            if(p[0]->next[0] == NULL || p[0]->next[0]->key != key){
                delete_res =0;
                return;
            }
            delete_res=1;
            Node* n =  p[0]->next[0];
            for(int l=0; l< height ; l++){
                p[l]->next[l] = n->next[l];
            }
            while(height > 1 || head->next[height-1]==NULL){
                height = height-1;
                head->next.pop_back();
                head->height=height;
            }
        }

        void show(){
            cur = head;
            for(long long int i=0; i < height; i++){
                while(cur->next[i]!=NULL){
                    long long int val = cur->next[i]->val;
                    cout <<"v:" <<val<< "h:"<<cur->next[i]->height<<" ";
                    cur = cur->next[i];
                }
            }
            cout << "\n";
        }
};

Skiplist sl;
GCL RNG2;
int main(){
    long long int S,U,B,N,F,I,D,P;
    scanf(" %lli",&S);
    scanf(" %lli",&U);
    scanf(" %lli",&B);
    scanf(" %lli",&N);
    scanf(" %lli",&F);
    scanf(" %lli",&I);
    scanf(" %lli",&D);
    scanf(" %lli",&P);


    RNG.set(S);
    RNG2.set(S);
    long long int k=0;

    /*
    vector<long long int > Y;
    */
    

    //cout<<"\npush3\n";
    for(long long int i=0; i < N; i++){
        long long int x = RNG.next() % (F+I+D);
        //find
        if( x < F){
            //cout<<"\ntryinf find\n";
            long long int v = RNG.next() %U;
            sl.search(v);
            if(k%P==0){
                cout <<"F "<<sl.find_nodes + 1<<" "<<sl.find_height<<"\n";
            }
            k++;
            
        }else if( F<= x  && x < F+I){
            //cout<<"\ntryinf insert\n";
            long long int v = RNG.next() %U;
            sl.insert(v); 
            if(k%P==0){
                cout <<"I " << sl.insert_res<<"\n";
            }
            k++;
            
        }else if(F+I <= x){
        //del
            //cout<<"\ntryinf del\n";
            long long int v = RNG.next() %U;
            sl.remove(v);
            if(k%P==0){
                cout <<"D " << sl.delete_res<<"\n";
            }
            k++;
        }

    }
        
}