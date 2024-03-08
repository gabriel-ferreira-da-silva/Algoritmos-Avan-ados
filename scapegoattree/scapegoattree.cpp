#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

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
Node* flat(Node* root,Node *p){
    vector<long long int> f = getv(root);
    //cout<<"merda\n";
    for(long int i=0;i<f.size();i++){
        //cout<<f[i] <<" ";
        p =  insert(p,f[i]);
    }
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
    nleft = (long long int) ceil((n-1)/2);
    nright = (long long int) floor((n-1)/2);
    Node* mid = new Node; 
    mid = build(head, nleft);
    Node* handle= new Node;
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
    Node *res = (build(head, n));
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
        r.node =root;
        r.n_node=0;
        r.tam=-1;
        r.rebuild=0;
        r.dis=-1;
        return r;
    }else if(key < root->key){
        r  = sgins(root->left, depth+1, n , alpha, key);
        root->left = r.node;
        nroot = r.rebuild!=0? 1 + r.tam + dfscount(root->right) : -1;
    }else{
        r  = sgins(root->right, depth+1, n , alpha, key);
        root->right = r.node;
        nroot = r.rebuild!=0? 1 + r.tam + dfscount(root->left) : -1;
    }
    r.dis = r.dis+1;
    if(r.rebuild && unbalanced(alpha, nroot, r.dis)){
        /*cout<<"\n\nrebuilding:\n";
        show(root);
        cout<<"\n";*/
        r.node = rebuild(root, nroot);
        r.n_node = r.n_node;
        r.tam = nroot;
        r.rebuild  = 0;
        r.dis=-1;
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



int main(){
    Node *root=NULL;
    Node *head;
    Node *dummy = new Node;
    root = insert(root, 4);
    root = insert(root, 2);
    root =insert(root, 1);
    root =insert(root, 3);
    root =insert(root, 5);
    root =insert(root, 6);
    root =insert(root, 7);
    /*
    show(root);
    cout<<"\n";
    root = flatten(root, dummy);
    show3(root);
    */
    Tree t;
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

    sginsert(&t, 143);
    show(t.root);
    cout<<"\n";
    sginsert(&t, 180);
    show(t.root);
    cout<<"\n";
    sginsert(&t, 343);
    show(t.root);
    cout<<"\n";
    sginsert(&t,8663);
    show(t.root);
    cout<<"\n";
    /*
    Tree hope;

    
    hope.root = insert(hope.root,3);
    hope.root = insert(hope.root,6);
    hope.root = insert(hope.root,1);
    hope.root = insert(hope.root,2);
    hope.root = insert(hope.root,7);
    hope.root = insert(hope.root,4);
    hope.root = insert(hope.root,5);
    
    hope.root = insert(hope.root,1000);

    cout<<"\n\n\n\n";
    show(hope.root);
    cout<<"\n\n\n\n";
    //hope.root = build(hope.root, 8)->left;
    Node *no =NULL;
    myflaterr(hope.root);
    cout<<"xixicoco\n";
    show(nn);
    */

   Tree i;
   i.root = insert(i.root, 56);
   i.root = insert(i.root, 3);
   i.root = insert(i.root, 10);
   i.root = insert(i.root, 331);
   i.root = insert(i.root, 106);
   i.root = insert(i.root, 103);
   i.root = insert(i.root, 51);
   i.root = insert(i.root, 116);

   Tree p;  
   /*vector<long long int> f = getv(i.root);
   cout<<"\n\n\nnexnextnext\n";
   for(long int i=0;i<f.size();i++){
    p.root = insert(p.root, f[i]);
   }*/
   p.root=NULL;
   p.root = flat(i.root, p.root);
   cout<<"\n\n\nnn\n";
   show(i.root);
   cout<<"\nasd\n";
   show(p.root);
   p.root = build(p.root, 8);
   cout<<"\n";
   show(p.root);
   


}