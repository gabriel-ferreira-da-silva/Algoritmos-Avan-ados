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
            if(p[0]->next[0] != NULL && p[0]->next[0]->key == key){
                p[0]->next[0]->val = val;
                return;
            }
            long int h = random_height();

            if(h > height){
                for(long int i = height ; i < h ; i++){
                    head->next[i] = NULL;
                }
                for(long int i = height ; i < h ; i++){
                    p[i] = head;
                }
                height = h;
            }

            Node* n =  new Node;
            n->next.resize(h);
            n->height=h;
            n->key = key;
            n->val = val;
            for(long int l=0; l < h; l++){
                n->next[l] = p[l]->next[l];
                p[l]->next[l] = n;
            }
        }

        Node* search(long int key){
            vector<Node*> p = precursors(key);
            if (p[0]->next[0] != NULL && p[0]->next[0]->key == key ){
                return p[0]->next[0];
            }else{
                return NULL;
            }
        }

        void show(){
            cur = head;
            for(long int i=0; i < height; i++){
                cur = head->next[i];
                while(cur!=NULL){
                    long int val = cur->val;
                    cout << val<< " ";
                    cur = cur->next[i];
                }
                cout << "\n ";
            }
        }




};


int main(){
    Skiplist sl;
    sl.insert(9,9);
    vector<Node*> p = sl.precursors(3);
    sl.show();
    printf("hello");
}