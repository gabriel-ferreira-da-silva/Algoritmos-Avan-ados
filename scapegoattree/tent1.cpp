#include<iostream>
#include<cmath>
#include<vector>
using namespace std;


#define A 1664525
#define C 1013904223
#define R 4294967296

long long int d1,d2;

class Node{
    public:
        Node *left, *right;
        long long int height;
        long long int key;

        Node(){
            left=right=NULL;
            height=0;
            key = -9999999;
        }
};

class Tree{
    public:
        Node *root;
        long long int size;
        double alpha;

        Tree(){
            size =0;
            root=NULL;
        }
};
Node* insert(Node *root, long long int key){
    if(root==NULL){
        Node *n = new Node;
        n->key = key;
        n->height=1;
        root = n;
        return root;
    }
    if(key==root->key){
        return root;
    }
    if(key > root->key){
        root->right = insert(root->right, key);
        return root;
    }else{
        root->left =insert(root->left , key);
        return root;
    }
}

void show(Node* root){
    if(root==NULL){
        return;
    }
    cout<<root->key<<" ";
    show(root->left);
    show(root->right);
}

void show2(Node* root){
    if(root==NULL){
        return;
    }
    show(root->left);
    show(root->right);
    cout<<root->key<<" ";
}

void show3(Node* root){
    if(root==NULL){
        return;
    }
    cout<<root->key<<" ";
    show(root->right);
    
}
void getflat(Node* root, vector<long long int> *v){
    if(root==NULL){
        return;
    }
    getflat(root->left, v);
    v->push_back(root->key);
    getflat(root->right, v);
}
vector<long long int> getv(Node* root){
    vector<long long int> *v = new vector<long long int>;

    getflat(root,v);
    return *v;
}
long long int universal=0;
Node* flat(Node* root,Node *p){
    vector<long long int> f = getv(root);
    //cout<<"merda\n";
    for(long int i=0;i<f.size();i++){
        //cout<<f[i] <<" ";
        p =  insert(p,f[i]);
    }
    universal = f.size();
    p = insert(p,9999999999);
    /*cout<<"ixi\n";
    show(p);
    cout<<"ixi\n";*/
    return p;
}


long long int dfscount(Node* node){
    if(node == NULL){
        return 0;
    }
    long long int l = dfscount(node->left);
    long long int r = dfscount(node->right);
    return l>r? l+1: r+1;
}

Node* flatten(Node *root, Node *head){
    if(root==NULL){
        return head;
    }
   
    root->right = flatten(root->right , head);
    return flatten(root->left ,  root);
}

Node* build(Node* head, long long int n){
    if(n==0){
        head->left = NULL;
        return head;
    }
    long long int nleft, nright;
    double in;
    in = (((double) n) - 1.0)/2.0; 
    nleft = (long long int) ceil(in);
    nright = n-1 - nleft;
    /*
    cout<<"  n-1/2= "<<in <<"\n";
    cout<<"  floor:"<<floor(in)<<" ceil:"<<ceil(in)<<"\n";
    cout<<"  inbuild nleft:"<<nleft<<" nright:"<<nright<<"\n";
    cout<<"  inbuild nleft:"<<nleft<<" nright:"<<nright<<"\n";
    cout<<"  n="<<n<<"\n";*/
    Node* mid = NULL; 
    mid = build(head, nleft);
    Node* handle= NULL;
    handle = build(mid->right, nright);
    mid->right = handle->left;
    handle->left = mid;
    return handle;
}


/*
Node* flat(Node* root){
    v.clear();
    myflat(root);
    Node *n;
    for(int i=0;i<v.size() ; i++){
        n = insert(n, v[i]);
    }
    cout<<"\n\n\nvai cafaaaaa\n";
    show(n);
    cout<<"vai cafaaaaa\\n\n\n\n\n\nn";

    return n;
}
*/
Node* rebuild(Node* root, long long int n){
    Node *dummy = new Node;
    //Node *head = flatten(root, dummy);
    Node *head=NULL;
    head = flat(root, head);
    /*cout<<"flat: ";
    show(head);
    cout<<"\n";*/
    Node *res = (build(head, universal));
    /*cout<<"rebuild noleft: ";
    show(res);
    cout<<"\n";*/
    return res->left;
}

long long int halpha(double alpha, long long int n){
    return (long long int) floor( log(n) / log(1/alpha));
}

int unbalanced(double alpha, long long int n, long long int i){
    if(i > halpha(alpha, n)){
        return 1;
    }
    return 0;
}

class res{
    public:
        Node *node;
        long long int n_node;
        long long int tam;
        int rebuild;
        long long int dis;
};
res sgins(Node* root, long long int depth, long long int n, double alpha, long long int key){
    res r;
    long long nroot;
    if(root==NULL){
        Node *node = new Node;
        node->key = key;
        long long int chg = depth > halpha(alpha,n+1);
        r.node = node;
        r.n_node = 1;
        r.tam=1;
        r.rebuild = chg;
        r.dis =0;
        return r;
    }else if(root->key == key){
        d1=-1;
        r.node =root;
        r.n_node=0;
        r.tam=-1;
        r.rebuild=0;
        r.dis=-1;
        return r;
    }else if(key < root->key){
        d1++;
        r  = sgins(root->left, depth+1, n , alpha, key);
        root->left = r.node;
        nroot = r.rebuild!=0? 1 + r.tam + dfscount(root->right) : -1;
    }else{
        d1++;
        r  = sgins(root->right, depth+1, n , alpha, key);
        root->right = r.node;
        nroot = r.rebuild!=0? 1 + r.tam + dfscount(root->left) : -1;
    }
    r.dis = r.dis+1;
    if(r.rebuild && unbalanced(alpha, nroot, r.dis)){
        /*cout<<"\n\nrebuilding: ";
        show(root);
        cout<<"\nre\n";*/

        r.node = rebuild(root, nroot);
        r.n_node = r.n_node;
        r.tam = nroot;
        r.rebuild  = 0;
        r.dis=-1;
        /*cout<<"rebuilded:";
        show(r.node);
        cout<<"\nre\n";*/
        return r;
    }
    r.node = root;
    r.n_node = r.n_node;
    r.tam = nroot;
    r.rebuild  = r.rebuild;
    r.dis=r.dis;
    return r;
}

void sginsert(Tree *t, long long int key){
    d1=0;
    res r = sgins(t->root, 0, t->size, t->alpha, key);
    t->root = r.node;
    t->size = t->size + r.n_node;
}

void flatten1(Node* root)
{
    // base condition- return if root is NULL or if it is a
    // leaf node
    if (root == NULL || root->left == NULL && root->right == NULL)
        return;
    // if root->left exists then we have to make it
    // root->right
    if (root->left != NULL) {
        // move left recursively
        flatten1(root->left);
        // store the node root->right
        Node* tmpRight = root->right;
        root->right = root->left;
        root->left = NULL;
        // find the position to insert the stored value
        Node* t = root->right;
        while (t->right != NULL) 
            t = t->right;
        // insert the stored value
        t->right = tmpRight;
    }
    // now call the same function for root->right
    flatten1(root->right);
}
class Rng{
    public:
        long long int x;

        long long int next(){
            long long int s= x;
            x = (A*x + C) % R;
            return s;
        }
    
};


void query(Node *root, long long int key){
    if(root==NULL){
        d2=-1;
        return;
    }
    if(root->key==key){
        return;
    }
    d2++;
    if(root->key < key){
        query(root->right, key);
    }else{
        query(root->left, key);
    }
}

void sgquery(Tree* sg, long long int key){
    d2=0;
    query(sg->root, key);
}

int main(){
    long long int S,U,B,N,I,Q,P;
    double alpha;
    
    scanf(" %lld", &S);
    scanf(" %lld", &U);
    scanf(" %lf", &alpha);
    scanf(" %lld", &B);
    scanf(" %lld", &N);
    scanf(" %lld", &I);
    scanf(" %lld", &Q);
    scanf(" %lld", &P);
    
    Rng  rng;
    rng.x = S;
    Tree sg;
    sg.alpha = alpha;
    for(long long int i=0 ; i < B ; i++){
        sginsert(&sg, rng.next()%U);
    }
    long long int x,y;
    for(long long int i=0; i < N; i++){
        x = rng.next()%(I+Q);
        if( x < I){
            y = rng.next() % U;
            sginsert(&sg, y);
            sgquery(&sg, y);
            if(d1<0 ||d2<0){
                d1=d2=-1;
            }
            if(i%P==0){
                cout<<"I "<<y<<" "<<d1<<" "<<d2<<"\n"; 
            }
        }else{
            y = rng.next() % U;
            sgquery(&sg, y);
            if(i%P==0){
                cout<<"Q "<<y<<" "<<d2<<"\n";
            }
        }
    }
}