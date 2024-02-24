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
    
    sl.insert(1,1);
    sl.insert(2,3);
    sl.insert(3,5);
    sl.insert(4,42);
    sl.insert(5,14);
    sl.insert(6,251);
    sl.insert(7,41);
    sl.insert(8,222);
    sl.insert(9,25);
    sl.insert(10,4513);
    sl.insert(11,2612);

    sl.show();

    cout<< "search 4: " << sl.search(4);
    cout<< "\nsearch 3: " << sl.search(3);
    cout<< "\nsearch 10: " << sl.search(10);
    cout<< "\nsearch 6: " << sl.search(6);
    cout<<"\n";

    sl.insert(1,1);
    sl.insert(2,3);
    sl.remove(4);
    sl.remove(4);
    sl.remove(10);

    sl.show();
    
    cout<< "search 4: " << sl.search(4);
    cout<< "\nsearch 3: " << sl.search(3);
    cout<< "\nsearch 10: " << sl.search(10);
    cout<< "\nsearch 6: " << sl.search(6);
}