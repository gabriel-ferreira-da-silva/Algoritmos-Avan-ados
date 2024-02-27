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
        return NULL;
    }
    if(root->key == key){
        return root;
    }
    if(root->key > key){
        return bst_search(root->left, key);
    }
    if(root->key < key){
        return bst_search(root->right, key);
    }
    return NULL;
}


Node* insert(Node *root, long long int key){
    if(root==NULL){
        Node* n = new Node;
        n->key=key;
        root=n;
        return root;
    }
    if( key > root->key){
        root->right = insert(root->right, key);
        root->right->par = root;
    }

    if( key < root->key){
        root->left =  insert(root->left, key);
        root->left->par = root;
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
    Node* x = bst_search(T->root,key);
    if(x!=NULL){
        T->root = splay(x);
    }
    return x;
}

long long int rng(long long int s){
    return (11*s + 4) % 15;
}

int main(){
    long long int s= 123, i =30 ;
    Splaytree st;
    Node *n = new Node;
    st.root = insert(st.root,  10);
    st.root = insert(st.root,  1);
    st.root = insert(st.root,  20);
    st.root = insert(st.root,  30);
    st.root = insert(st.root,  25);
    
    show(st.root);
    std::cout <<"\n";
    
    n = find(&st, 20);
    show(st.root);
    std::cout <<"\n";

    st.root = insert(st.root,  100);
    st.root = insert(st.root,  5);
    n = find(&st, 1);
    show(st.root);
    std::cout <<"\n";

    
    st.root = insert(st.root,  60);
    st.root = insert(st.root,  413);
    n = find(&st, 4441);
    show(st.root);
    std::cout <<"\n";

    st.root = insert(st.root,  36);
    st.root = insert(st.root,  43);
    n = find(&st, 41);
    show(st.root);
    std::cout <<"\n";

    
    st.root = insert(st.root,  35);
    st.root = insert(st.root,  78);
    n = find(&st, 36);
    show(st.root);
    std::cout <<"\n";
    
    
    n = find(&st, 78);
    show(st.root);
    std::cout <<"\n";
    
    

}