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
}

Node* rotate_right(Node* x){
    if(x == NULL){
        return NULL;
    }
    if(x->left==NULL){
        return NULL;
    }
    
    Node *L,*P,*LR;

    P = x->par;
    L = x->left;
    LR = L->right;

    x->left = LR;
    if(LR !=NULL){
        LR->par = x;
    }

    L->right = x;
    x->par = L;
    L->par = P;

    if(P!=NULL && x==P->left){
        P->left = L;
    }else if(P!= NULL && x == P->right){
        P->right = L;
    }
    return L;    
}
Node* rotate_left(Node* x){
    if(x == NULL){
        return NULL;
    }
    if(x->right !=NULL){
        return NULL;
    }
    
    Node *R,*P,*RL;

    P = x->par;
    R = x->right;
    RL = R->left;

    x->right = RL;
    if(RL !=NULL){
        RL->par = x;
    }

    R->left = x;
    x->par = R;
    R->par = P;

    if(P!=NULL && x==P->left){
        P->left = R;
    }else if(P!= NULL && x == P->right){
        P->right = R;
    }
    return R;
} 

Node* zig(Node* x){
    Node* P = x->par;
    if(P == NULL){
        return NULL;
    }
    if(x == P->left){
        return rotate_right(P);
    }else{
        return rotate_left(P);
    }
}

Node* zigzag( Node* x){
    Node* P  = x->par;
    if(P == NULL){
        return NULL;
    }
    Node* G = P->par;
    if(G == NULL){
        return NULL;
    }

    if( P == G->left){
        if(x == P->left){
            rotate_right(G);
            return rotate_left(P);
        }else{
            rotate_left(P);
            return rotate_right(G);
        }
    }else{
        if(x == P->right){
            rotate_left(G);
            return rotate_right(P);
        }else{
            rotate_right(P);
            return rotate_left(G);
        }
    }
}




Node* splay(Node* x){
    while(x->par != NULL){
        Node* G = x->par->par;
        if(G!=NULL){
            x = zig(x);
        }else{
            x=zigzag(x);
        }
    }
    return x;
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

Node* find( Splaytree *st, long long int key){
    Node* x = bst_search(st->root, key);
    printf("caguei1\n");
    if(x!=NULL){
        st->root = splay(x);
    }
    return x;   
}

void show(Node* s){
    if(s==NULL){
        return;
    }
    printf("%lld ", s->key);
    show(s->left);
    show(s->right);

}

long long int rng(long long int s){
    return (11*s + 4) % 15;
}

int main(){
    long long int s= 123, i =30 ;
    Splaytree st;
    /*
    while(i--){
        s = rng(s);
        if(s%5==0 ){
            s=rng(s);
            printf("find: %lld-res:\n", s, find(&st,s));
            show(st.root);
            printf("\n");

        }else{
            s = rng(s);
            st.root = insert(st.root, s);
            printf("ins: %lld\n", s);
            
        }
    }
    show(st.root);
    std::cout <<"\n";
    */
    
    st.root = insert(st.root, 1);
    st.root = insert(st.root, 99);
    st.root = insert(st.root, 134);
    show(st.root);
    printf("\n");
    find(&st, 99);
    show(st.root);
    printf("\n");
    st.root = insert(st.root, 34);
    st.root = insert(st.root, 61);
    st.root = insert(st.root, 234);
    st.root = insert(st.root, 45);
    st.root = insert(st.root, 78);
    show(st.root);
    printf("\n");
    find(&st, 234);
    show(st.root);
    printf("\n");
    st.root = insert(st.root, 31);
    st.root = insert(st.root, 8);
    st.root = insert(st.root, 7);
    st.root = insert(st.root, 15);
    show(st.root);
    printf("\n");
    find(&st, 8);
    show(st.root);
    printf("\n");
    st.root = insert(st.root, 14);
    st.root = insert(st.root, 5);
    show(st.root);
    printf("\n");
    find(&st, 14);
    show(st.root);
    printf("\n");

}