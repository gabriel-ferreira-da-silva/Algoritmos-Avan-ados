#include<iostream>
#include<vector>
using namespace std;


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
        Node *button  = new Node;
        Node *top  = new Node;
        vector<Node> stack;

        Minstack(){
            button->next = NULL;
            button->min = NULL;
        }

        void push(int val){
            
            Node *n = new Node;
            n->val = val;
            if(stack.size() == 0){
                n->val = val;
                n->next = NULL;
                n->min = n;
            }else if(stack.end()->min->val > val ){
                n->val = val;
                n->next = NULL;
                n->min = n;
            }else{
                n->next = &stack[stack.size() -1 ];
                n->min = stack[stack.size() -1 ].min;
            }
            stack.push_back(*n);
        }


        int showMin(){
            if(stack.size()>0){
                return stack[stack.size()-1].min->val;
            }else{
                return -1;
            }
            
        }

};