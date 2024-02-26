#include<iostream>
#include<vector>
using namespace std;

#define R 4294967296
#define A 1664525
#define C 1013904223


class GCL{
    public:
        long int X;
        GCL(long int s){
            X=s;
        }

        long int next(){
            long int a=X;
            X = (A * X + C) % R;
            return a;
        }
};

class Node{
    public:
        long int val;
        long int key;
        long int height;
        vector<Node*> next;
};

class Skiplist{
    public:
        Node *head = new Node;
        Node *cur = new Node;

        long int height =1;
        
        long int delete_res;
        long int insert_res;

        long int find_nodes;
        long int find_height;

        Skiplist(){
            head->next.push_back(NULL);
            head->height=1;
            head->val=0;
            head->key=-9999999;
            height = 1;
        }

        vector<Node*> precursors(long int key){
            vector<Node*> P(height, NULL);

            find_nodes =1;
            find_height=0;
            cur = head;
            for(long int l = height-1; l >= 0 ; l--){
                //cout<<"xixi";
                while(cur->next[l] != NULL && cur->next[l]->key < key){
                    cur = cur->next[l];
                    find_nodes+=1;
                    //cout<<"merda\n";
                }
                P[l] = cur;
                //cout<<"cooco\n";
            }
            //cout<<"is thios?\n";
            //find_height=P[0]->next[0]->height;
            return P;
        }

        long int random_height( GCL *H){
            long int h=1;
            long int max_height = height+1;
            while(H->next() % 100 < 50 && h<max_height){
                h+=1;
            }
            return h;
        }

        void insert(long int key, GCL *H){
            //cout<<"caguei1\n";
            vector<Node*> p = precursors(key);
            //cout<<"caguei1\n";
            if(p[0]->next[0]!= NULL && p[0]->next[0]->key == key){
                p[0]->next[0]->val=key;
                insert_res = 0;
                return;
            }
            insert_res=1;
            //cout<<"caguei2\n";
            long int h=random_height(H);
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

        long int search(long int key){
            vector<Node*> p = precursors(key);
            if (p[0]->next[0] != NULL && p[0]->next[0]->key == key ){
                return p[0]->next[0]->key;
            }else{
                return -1;
            }
        }

        void remove(long int key){
            vector<Node*> p = precursors(key);
            
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
            for(long int i=0; i < height; i++){
                while(cur->next[i]!=NULL){
                    long int val = cur->next[i]->val;
                    cout <<"v:" <<val<< "h:"<<cur->next[i]->height<<" ";
                    cur = cur->next[i];
                }
            }
            cout << "\n";
        }
};

int main(){
    Skiplist sl;
    long int S,U,B,N,F,I,D,P;
    cin >> S>>U>>B>>N>>F>>I>>D>>P;
    GCL RNG(S);

    vector<long int> y;
    cout<<"\npush1\n";
    for(long int i=0; i < B; i++){
        long int Y = RNG.next()%U;
        y.push_back(Y);
    }
    cout<<"\npush2\n";
    for(long int i=0; i < B; i++){
        sl.insert(y[i],&RNG);
    }
    cout<<"\npush3\n";
    for(long int i=0; i < N; i++){
        long int x = RNG.next() % (F+I+D);
        
        //find
        if( x < F){
            cout<<"\ntryinf find\n";
            long int v = RNG.next() %U;
            sl.search(v);
            cout <<"F "<<sl.find_nodes<<" "<<sl.find_height<<"\n";
        }
        //ins
        else if( F<= x  && x < F+I){
            cout<<"\ntryinf insert\n";
            long int v = RNG.next() %U;
            sl.insert(v, &RNG);
            cout <<"I " << sl.insert_res<<"\n";
        }else{
        //del
            cout<<"\ntryinf del\n";
            long int v = RNG.next() %U;
            sl.remove(v);
            cout <<"D " << sl.delete_res<<"\n";
        }

    }
    




    
}