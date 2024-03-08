#include<iostream>
#include<cmath>

using namespace std;


class Node{
    public:
        long long int key;
        Node *left, *right;

        Node(){
            left = NULL;
            right = NULL;
        }
};

class res{
    public:
        Node* node=new Node;
        long long int n_nodes;
        long long int newtam;
        long long int needrebuild;
        long long int dist;
};

class sgtree{
    public:
        Node *root = new Node;
        double alpha;
        long long int size;
        sgtree(){
            size=0;
            root=NULL;
        }
};

long long int halpha( long long int n,double alpha){
    /*cout<<"\nhalpha:\n";
    cout<<"alpha:"<<alpha<<"\n";
    cout<<"result:"<< (long long int) floor((log( (double) n) / log( 1/alpha))) <<"\n";*/
    return (long long int) floor((log( (double) n) / log( 1/alpha)));
}

long long int dfscount(Node* node){
    if(node == NULL){
        return 0;
    }
    long long int l = dfscount(node->left);
    long long int r = dfscount(node->right);
    return l>r? l+1: r+1;
}

long long int unbalanced(double alpha, long long int n, long long int i){
    return i > halpha(n, alpha);
}

Node* flatten(Node* root, Node* head){
    if(root==NULL){
        return head;
    }
    root->right = flatten(root->right, head);
    return flatten(root->left, root);
}

Node* build(Node* head, long long int n){
    if(n==0){
        head->left = NULL;
        return head;
    }
    long long int nleft,nright;
    Node* mid=new Node;
    Node* handle=new Node;
    
    nleft = (long long int) ceil((n-1)/2);
    nright = (long long int) floor((n-1)/2);
    mid = build(head, nleft);
    handle = build(mid->right, nright);
    mid->right = handle->left;
    handle->left = mid;
    return handle;
}

void show(Node *root){
    if(root==NULL){
        return;
    }
    
    show(root->left);
    printf("%lld ", root->key);
    show(root->right);
}

void show2(Node *root){
    if(root==NULL){
        return;
    }
    
    
    printf("%lld ", root->key);
    show2(root->left);
    show2(root->right);
}

void show3(Node *root){
    if(root==NULL){
        return;
    }
    
    show3(root->left);
    show3(root->right);
    printf("%lld ", root->key);
}

Node* rebuild(Node* root, long long int n){
    Node* dummy = new Node;
    Node* head = flatten(root, dummy);
    /*cout<<"merd\n";
    show(head);
    cout<<"\n";*/
    return build(head,n)->left;
}
res *r = new res;

res* sgins(Node* root, long long int depth, long long int n, double alpha, long long int key ){
    long long int nroot;
    if(root==NULL){
        Node *node = new Node;
        node->key = key;
        r->node = node;
        r->n_nodes = 1;
        r->newtam=1;
        r->needrebuild = depth > halpha(n+1, alpha);
        r->dist = 0;
        return r;
    }else if(key==root->key){
        r->node = root;
        r->n_nodes = 0;
        r->newtam = -1;
        r->needrebuild = 0;
        r->dist=-1;
        return r;
    }else if(key < root->key){
        r = sgins(root->left, depth+1, n, alpha, key);
        root->left = r->node;
        //cout << root->key <<" "<<root->left->key<<"\n";
        nroot = r->needrebuild==1 ? 1 + r->newtam + dfscount(root->right) : -1;
    }else{
        r = sgins(root->right, depth+1, n, alpha, key);
        root->right = r->node;
        // não seria dfscoutn(root->left) ???????
        nroot = r->needrebuild==1 ? 1 + r->newtam + dfscount(root->left) : -1;
    }

    r->dist = r->dist+1;
    //cout << root->key <<" "<<root->left->key<<"\n";
    if(r->needrebuild && unbalanced(alpha, nroot, r->dist)){
        cout<<"rebuilding\n";
        r->node =  rebuild(root, nroot);
        cout<<"re:\n";
        show(r->node);
        cout<<"\n";
        show2(r->node);
        cout<<"\ner\n";
        r->n_nodes = r->n_nodes;
        r->newtam = nroot;
        r->needrebuild = 0;
        r->dist =-1;
        return r;
    }

    r->node=root;
    r->newtam = nroot;
    //cout << root->key <<" "<<root->left->key<<"\n";
    return r;
}

void sginsert(sgtree* sg, long long int key){
    res *re  = sgins(sg->root, 0, sg->size, sg->alpha, key);
    sg->root = r->node;
    sg->size = sg->size + r->n_nodes;
}

int main(){
    sgtree sgt;

    sgt.alpha = 0.5;

    
    sginsert(&sgt, 4);
    show(sgt.root);
    cout<<"\n";

    sginsert(&sgt, 2);
    show(sgt.root);
    cout<<"\n";

    sginsert(&sgt, 5);
    show(sgt.root);
    cout<<"\n";

    sginsert(&sgt, 1);
    show(sgt.root);
    cout<<"\n";

    sginsert(&sgt, 3);
    show(sgt.root);
    cout<<"\n";
    show2(sgt.root);
    cout<<"\n";

    sginsert(&sgt, 6);
    show(sgt.root);
    cout<<"\n";
    show2(sgt.root);
    cout<<"\n";
    show3(sgt.root);
    cout<<"\n";

    sginsert(&sgt, 7);
    show(sgt.root);
    cout<<"\n";
    show2(sgt.root);
    cout<<"\n";
    show3(sgt.root);
    cout<<"\n";

    
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";

    sgtree t;
    t.alpha = 0.5;
    
    sginsert(&t, 10);
    show(t.root);
    cout<<"\n";
    sginsert(&t, 1);
    show(t.root);
    cout<<"\n";
    sginsert(&t, 4);
    show(t.root);
    cout<<"\n";
    sginsert(&t, 20);
    show(t.root);
    cout<<"\n";
    sginsert(&t, 8);
    show(t.root);
    cout<<"\n";
    sginsert(&t, 25);
    show(t.root);
    cout<<"\n";
    sginsert(&t, 43);
    show(t.root);
    cout<<"\n";
    sginsert(&t, 18);
    show(t.root);
    cout<<"\n";
    sginsert(&t, 3);
    show(t.root);
    cout<<"\n";

}