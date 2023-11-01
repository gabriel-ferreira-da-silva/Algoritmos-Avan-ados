#include<iostream>

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