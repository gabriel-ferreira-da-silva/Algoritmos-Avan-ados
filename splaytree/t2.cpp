#include<iostream>


class Node{
    public:
        long long int key;
        Node *left, *right, *par;
        Node(){
            left=NULL;
            right=NULL;
            par=NULL;
        }
};


long long int D=0;

class Splaytree{
    public:
        Node *root  = NULL;
};

Node* rotate_left(Node* x){
    if(x==NULL) return NULL;
    if(x->right == NULL) return NULL;
    Node *P,*R,*RL;
    P = x->par;
    R = x->right;
    RL = R->left;
    x->right = RL;
    if(RL!=NULL) RL->par = x;
    R->left = x;
    x->par = R;
    R->par = P;
    if(P!=NULL && x==P->left){
        P->left = R;
    }else if(P!=NULL && x==P->right){
        P->right = R;
    }
    return R;
}

Node* rotate_right(Node* x){
    if(x==NULL) return NULL;
    if(x->left == NULL) return NULL;
    Node *P,*L,*LR;
    P = x->par;
    L = x->left;
    LR = L->right;
    x->left = LR;
    if(LR!=NULL) LR->par = x;
    L->right = x;
    x->par = L;
    L->par = P;
    if(P!=NULL && x==P->left){
        P->left = L;
    }else if(P!=NULL && x==P->right){
        P->right = L;
    }
    return L;
}

Node* bst_search( Node *root, long long int key){
    if(root==NULL){
        D=-1;
        return NULL;
    }
    if(root->key == key){
        return root;
    }
    
    if(root->key > key){
        D+=1;
        return bst_search(root->left, key);
    }
    if(root->key < key){
        D+=1;
        return bst_search(root->right, key);
    }
    return NULL;
}


Node* insert(Node *root, long long int key){
    D+=1;
    if(root==NULL){
        Node* n = new Node;
        n->key=key;
        root=n;
        return root;
    }
    if( key > root->key){
        root->right = insert(root->right, key);
        root->right->par = root;
    }else if( key < root->key){
        root->left =  insert(root->left, key);
        root->left->par = root;
    }else{
        D=-1;
    }
    return root;
}


void show(Node* s){
    if(s==NULL){
        return;
    }
    printf("k:%lldp:%lld ", s->key,(s->par==NULL? -1 : s->par->key));
    show(s->left);
    show(s->right);
}

Node* zig(Node* x){
    if(x == NULL) return NULL;
    if(x->par == NULL) return NULL;
    Node* P = x->par;
    if(x==P->left){
        return rotate_right(P);
    }else{
        return rotate_left(P);
    }
}

Node* zigzag(Node* x){
    if(x==NULL) return NULL;
    if(x->par==NULL) return NULL;
    if(x->par->par==NULL) return NULL;
    Node *P = x->par;
    Node *G = P->par;

    if(P==G->left){
        if(x==P->left){
            G = rotate_right(G);
            return rotate_right(P);
        }else{
            P = rotate_left(P);
            return rotate_right(G);
        }
    }else{
        if(x==P->right){
            G = rotate_left(G);
            return rotate_left(P);
        }else{
            P = rotate_right(P);
            return rotate_left(G);
        }
    }
}

Node* splay(Node* x){
    if(x==NULL) return NULL;
    while(x->par!=NULL){
        Node *G  = x->par->par;
        if(G==NULL){
            x = zig(x);
        }else{
            x =zigzag(x);
        }
    }
    return x;
}

Node* find(Splaytree *T, long long int key){
    D=0;
    Node* x = bst_search(T->root,key);
    if(x!=NULL){
        T->root = splay(x);
    }
    return x;
}


#define R 4294967296
#define A 1664525
#define C 1013904223

long long int rng(long long int s){
    return (A*s + C) % R;
}

int main(){
    long long int S,U,B,N,I,Q,P;
    scanf(" %lld %lld %lld %lld %lld %lld %lld", &S, &U, &B, &N, &I, &Q, &P);
    printf(" %lld %lld %lld %lld %lld %lld %lld\n", S, U, B, N, I, Q, P);
    long long int x = S;
    Splaytree t;
    for(long long int i = 0; i < B ;i++){
        t.root = insert(t.root, x);
        x= rng(x);
    }
    
    for(long long int i = 0; i < N ;i++){
        if( x %(I+Q) < I){
            x=rng(x);
            long long int k = x%U;
            x=rng(x);        
            D=-1;
            t.root = insert(t.root, k);
            if(i % P ==0){
                std::cout << "I "<<k<<" "<<D<<"\n"; 
            }        
        }else{
            x=rng(x);
            long long int k = x%U;
            x=rng(x);
            D=0;
            find(&t, k);
            if(i % P ==0){
                std::cout << "Q "<<k<<" "<<D<<" -"; 
                show(t.root);
                printf("\n");
            }
        }    
    }
}