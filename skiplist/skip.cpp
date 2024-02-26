#include<iostream>
#include<vector>
using namespace std;

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

        Skiplist(){
            head->next.push_back(NULL);
            head->height=1;
            head->val=0;
            head->key=-9999999;
            height = 1;
        }

        vector<Node*> precursors(long int key){
            vector<Node*> P(height, NULL);
            cur = head;
            for(long int l = height-1; l >= 0 ; l--){
                while(cur->next[l] != NULL && cur->next[l]->key < key){
                    cur = cur->next[l];
                }
                P[l] = cur;
            }
            return P;
        }

        long int random_height(){
            return height+1;
        }

        void insert(long int key, long int val){
            vector<Node*> p = precursors(key);
            if(p[0]->next[0]!= NULL && p[0]->next[0]->key == key){
                p[0]->next[0]->val=val;
                return;
            }

            long int h=random_height();
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

            Node* n = new Node();
            vector<Node*> a(h, NULL);
            n->height = h;
            n->next = a;
            n->key = key;
            n->val = val;

            for(int l =0; l<h;l++){
                n->next[l] = p[l]->next[l];
                p[l]->next[l] = n;
            }

        }

        long int search(long int key){
            vector<Node*> p = precursors(key);
            if (p[0]->next[0] != NULL && p[0]->next[0]->key == key ){
                return p[0]->next[0]->val;
            }else{
                return -1;
            }
        }

        void remove(long int key){
            vector<Node*> p = precursors(key);
            
            if(p[0]->next[0] == NULL || p[0]->next[0]->key != key){
                return;
            }
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
    
    long int a,b,c;
    a =3;
    c=1000;
    while(c > 0){
        c--;
        b = (c*a + b*b) % 1000;
        a = a*a*a +b*a + c*b;
        sl.insert(a+b, a+b);
        if(a%3==0){
            sl.search((a+b+c)%1000);
        }
        if(a%5==0){
            sl.remove((a+b+c)%1000);
        }
    }
}